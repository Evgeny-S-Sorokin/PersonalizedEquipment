// Script File

class EntitySpawner
{

	//-----------------------------------------------------------------------------------------
	// private:
	static protected string	_container_name;
	static protected int 	_entity_spawn_delay;
	static protected int	_entity_despawn_delay;
	static protected int	_recursion_depth_max;
	static protected bool	_is_entity_persistent;

	static protected ref array< PlayerBase > _g_corpses;	
	static protected ref array< EntityAI >   _g_entities;

	static protected int 		_recursion_depth = 0;
	static protected EntityAI	_main_container;

	//-----------------------------------------------------------------------------------------
	// public:
	
	//-Constructor--------------------------------------------
	void EntitySpawner()
	{
		// Set EntitySpawner parameters
		ref EntitySpawnerCfg cfg 	= new ref EntitySpawnerCfg;
		_container_name 			= cfg.get_container_name();
		_entity_spawn_delay			= cfg.get_entity_spawn_delay();
		_entity_despawn_delay		= cfg.get_entity_despawn_delay();
		_recursion_depth_max		= cfg.get_recursion_depth_max();
		_is_entity_persistent		= cfg.get_entity_persistence();
		
		// Set corpses and entity listeners and arrays for them
		_g_corpses 	= new ref array< PlayerBase >;
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( spawn_entity, _entity_spawn_delay * 1000, true );		
		if ( !_is_entity_persistent )
		{
			_g_entities = new ref array< EntityAI >;
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( despawn_entity, _entity_despawn_delay * 1000, true );
		}
		else {}
	}
	
	//-_g_corpse interfaces------------------------
	static void push_back_corpse( notnull PlayerBase corpse )
	{
		_g_corpses.Insert( corpse );
	}
	
	//-Entity spawner-----------------------------------------
	static void spawn_entity()
	{
		string func_name = "spawn_entity";
		
		g_log.trace( "Trying to spawn entity: ", func_name );
		g_log.trace( _g_corpses.Count().ToString(), func_name );
		
		if ( _g_corpses.Count() > 0 )
		{
			foreach ( auto ind, auto corpse : _g_corpses )
			{
				if ( corpse != null )
				{
					auto created_object = create_object_with_players_items( corpse );
					if ( created_object != null ) 
					{
						_g_entities.Insert( created_object );
						GetGame().ObjectDelete( corpse );
					}
					else {}
				}
				else {}
			}
			_g_corpses.Clear();
		}
		else {}
	}
	
	//-Entity despawner---------------------------------------
	static void despawn_entity()
	{
		string func_name = "despawn_entity";
		g_log.trace( "Trying to despawn entity: ", func_name );
		g_log.trace( _g_entities.Count().ToString(), func_name );
		
		if ( _g_entities.Count() > 0 )
		{
			foreach ( auto ind, auto entity : _g_entities )
			{
				GetGame().ObjectDelete( entity );
			}
			_g_entities.Clear();
		}
	}
	
	//-creates item on player's position with items of player-
	static EntityAI create_object_with_players_items( notnull PlayerBase corpse )
	{	
		auto corpse_inventory = corpse.GetInventory();
		
		if ( corpse_inventory == null )
		{
			return null;
		}
		else 
		{		
			// SpawnEntity
			EntityAI object_to_spawn_ai = EntityAI.Cast( GetGame().CreateObject( _container_name, corpse.GetPosition(), false, true ) );
			
			if ( object_to_spawn_ai != null )
			{
				object_to_spawn_ai.SetOrientation( "0 0 0" );
				_main_container = object_to_spawn_ai;
				
				// Check player's hand
				if ( corpse.GetHumanInventory() != null )
				{
					EntityAI attachment_in_hand = corpse.GetHumanInventory().GetEntityInHands();
					if ( attachment_in_hand != null )
					{
						_try_to_move_object_recursively( object_to_spawn_ai, attachment_in_hand );
					}
					else {}
				}
				else {}
				
				// Check whole player's inventory
				int att_ind_max = corpse_inventory.AttachmentCount();
				for ( int att_ind = 0; att_ind < att_ind_max; ++att_ind )
				{
					EntityAI attachment = corpse_inventory.GetAttachmentFromIndex( att_ind );
					_try_to_move_object_recursively( object_to_spawn_ai, attachment );		
				}
				
				_main_container = null;
			} // if ( object_to_spawn_ai ... )
			else {}
			
			return object_to_spawn_ai;
		} // if ( corpse_inventory ... ) {} else			
	}
	
	//-----------------------------------------------------------------------------------------	
	//private:
	
	//-If item_to_put is attachment
	//-Tries to copy <item_to_put> into its original carrier then deletes it-
	//-If item_to_put is cargo item
	//-Tries to copy <item_to_put> into its main container then deletes it-
	protected static void _try_to_move_object_recursively( notnull EntityAI object_to_fill, notnull EntityAI item_to_put )
	{		
		string func_name = "_try_to_move_object_recursively";
		++_recursion_depth;
		
		g_log.trace( "Trying to put" + item_to_put.GetType() + " into " + object_to_fill.GetType(), func_name );
		g_log.trace( "Recurtion depth: ", func_name );
		g_log.trace( _recursion_depth.ToString(), func_name );
		
		if ( _recursion_depth < _recursion_depth_max )
		{
			// Create a copy of an item to put in container
			EntityAI created_copy = object_to_fill.GetInventory().CreateInInventory( item_to_put.GetType() );
			if ( created_copy != null ) 
			{
				created_copy.SetHealth( "", "", item_to_put.GetHealth( "", "" ) );
				
				// Check if item has anything inside
				if ( item_to_put.GetInventory() != null ) 
				{		
						
					// Put attachments on the copy		
					int item_to_put_att_count = item_to_put.GetInventory().AttachmentCount();
					for ( int att_ind = 0; att_ind < item_to_put_att_count; ++att_ind )
					{
						EntityAI item_to_put_attachment = item_to_put.GetInventory().GetAttachmentFromIndex( att_ind );
						_try_to_move_object_recursively( created_copy, item_to_put_attachment );					
					}	
					
					// Put the cargo of the copy
					CargoBase cargo = item_to_put.GetInventory().GetCargo();
					if ( cargo != null )
					{
						int item_to_put_cargo_count = cargo.GetItemCount();
						for ( int cargo_ind = 0; cargo_ind < item_to_put_cargo_count; ++cargo_ind )
						{
							EntityAI item_to_put_cargo = cargo.GetItem( cargo_ind );
							_try_to_move_object_recursively( _main_container, item_to_put_cargo );
						}				
					}
					else {}
					
					// Put the mag of the copy if it's a weapon
					if ( item_to_put.IsWeapon() )
					{
						Weapon_Base weapon_to_put = Weapon_Base.Cast( item_to_put );
						Magazine item_to_put_mag = weapon_to_put.GetMagazine( weapon_to_put.GetCurrentMuzzle() );
						if ( item_to_put_mag != null )
						{
							Magazine created_mag = Magazine.Cast( _main_container.GetInventory().CreateInInventory( item_to_put_mag.GetType() ) );
							created_mag.SetHealth( "", "", item_to_put_mag.GetHealth( "", "" ) );
							created_mag.LocalSetAmmoCount( item_to_put_mag.GetAmmoCount() );
						}
						else {}
					} 
					else {}
					
				} // if ( item_to_put.GetInventory() ... )
				else {}				
			} // if ( created_copy ... )
			else {}	
		} // if ( recursion_depth ... )
		else {}
		
		item_to_put.Delete();				
		--_recursion_depth;
	}
	
	//-----------------------------------------------------------------------------------------
	
}

// Global initialization
ref EntitySpawner g_EntitySpawner;