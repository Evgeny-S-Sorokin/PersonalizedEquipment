// Script File

modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		
		// TBD
		g_EntitySpawner = new EntitySpawner;
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{		
		Entity playerEnt;
		
		ref Alastor_PlayerCfg cfg 	= new ref Alastor_PlayerCfg( identity );		
		auto player_spawn_type 		= cfg.get_spawn_type();
		auto player_loadout_type 	= cfg.get_loadout_type();
		characterName  				= cfg.get_face();
		
		ref Alastor_SpawnCfg cfg_spawn	= new ref Alastor_SpawnCfg( player_spawn_type );		
		pos[0] = cfg_spawn.get_x();
		pos[2] = cfg_spawn.get_z();
		pos[1] = GetGame().SurfaceY( pos[0], pos[2] );
		
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE"); //Creates random player		
		Class.CastTo(m_player, playerEnt);
		
		m_player.set_spawn_type( player_spawn_type );
		m_player.set_loadout_type( player_loadout_type );
		
		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}

	override void StartingEquipSetup( PlayerBase player, bool clothesChosen )
	{		
		string func_name = "StartingEquipSetup";
		
		player.RemoveAllItems();
		
		g_log.debug_info( "Loading cfg", func_name );		
		ref Alastor_LoadoutCfg cfg = new ref Alastor_LoadoutCfg( player.get_loadout_type() );
			
		// Head
		create_items_on_slot( player, cfg.slot_mask, null, null );
		create_items_on_slot( player, cfg.slot_eyewear, null, null );			
		create_items_on_slot( player, cfg.slot_headgear, cfg.slot_headgear_attachments, cfg.slot_headgear_cargo );
		
		// Shoulders
		create_items_on_slot( player, cfg.slot_shoulder_1, cfg.slot_shoulder_1_attachments, cfg.slot_shoulder_1_cargo );		
		create_items_on_slot( player, cfg.slot_shoulder_2, cfg.slot_shoulder_2_attachments, cfg.slot_shoulder_2_cargo );
		
		// Hands		
		auto new_item = player.GetHumanInventory().CreateInHands( cfg.slot_hands );
		g_log.trace( "Item: [" + new_item.GetType() + "] created", func_name );
		fill_item( new_item, cfg.slot_hands_attachments );
		fill_item( new_item, cfg.slot_hands_cargo );
		
		create_items_on_slot( player, cfg.slot_gloves, null, null );	
		create_items_on_slot( player, cfg.slot_armband, cfg.slot_armband_attachments, cfg.slot_armband_cargo );
		
		// Torso
		create_items_on_slot( player, cfg.slot_vest, cfg.slot_vest_attachments, cfg.slot_vest_cargo );		
		create_items_on_slot( player, cfg.slot_body, cfg.slot_body_attachments, cfg.slot_body_cargo );		
		create_items_on_slot( player, cfg.slot_back, cfg.slot_back_attachments, cfg.slot_back_cargo );		
		create_items_on_slot( player, cfg.slot_hips, cfg.slot_hips_attachments, cfg.slot_hips_cargo );
		
		// Legs
		create_items_on_slot( player, cfg.slot_legs, cfg.slot_legs_attachments, cfg.slot_legs_cargo );		
		create_items_on_slot( player, cfg.slot_feet, cfg.slot_feet_attachments, cfg.slot_feet_cargo );
		
	}
	
	
	
	protected void delete_items( notnull PlayerBase player )
	{
		string func_name = "delete_items";
		
		auto smth_in_hands = player.GetHumanInventory().GetEntityInHands();
		if ( smth_in_hands )
		{
			GetGame().ObjectDelete( smth_in_hands );
		}
		else {}
		
		auto ind_max = player.GetInventory().GetAttachmentSlotsCount();
		EntityAI item_to_delete;
		g_log.trace( "Items to delete amount: " + ind_max.ToString(), func_name );
		for ( int ind = 0; ind < ind_max; ++ind )
		{
			if ( player != null && player.GetInventory() != null )
			{ 
				item_to_delete = player.GetInventory().GetAttachmentFromIndex( ind );
				if ( ( item_to_delete != null ) && item_to_delete.IsItemBase() )
				{
					g_log.trace( "Deleted: " + item_to_delete.GetType(), func_name );
					GetGame().ObjectDelete( item_to_delete );
				}
				else {}
			}
			else {}
		}
	}
	
	protected void create_items_in_hands( notnull PlayerBase player, string main_item, array< string > main_item_att, array< string > main_item_cargo )
	{
		string func_name = "create_items_in_hand";
		
		auto new_item = player.GetHumanInventory().CreateInHands( main_item );
		if ( new_item != null )
		{
			g_log.trace( "Item: [" + new_item.GetType() + "] created", func_name );
			
			if ( main_item_att != null )
			{
				fill_item( new_item, main_item_att );
			}
			else {}
			
			if ( main_item_cargo != null )
			{
				fill_item( new_item, main_item_cargo );
			}
			else {}
		}
		else 
		{
			g_log.debug_info( "Failed to create [" + main_item + "].", func_name );
		}
		
	}
	
	protected void create_items_on_slot( notnull PlayerBase player, string main_item, array< string > main_item_att, array< string > main_item_cargo )
	{
		string func_name = "create_items_on_slot";
		auto new_item = player.GetInventory().CreateInInventory( main_item );
		if ( new_item != null )
		{
			g_log.trace( "Item: [" + new_item.GetType() + "] created", func_name );
			
			if ( main_item_att != null )
			{
				fill_item( new_item, main_item_att );
			}
			else {}
			
			if ( main_item_cargo != null )
			{
				fill_item( new_item, main_item_cargo );
			}
			else {}
		}
		else 
		{
			g_log.debug_info( "Failed to create [" + main_item + "].", func_name );
		}
	}
		
	protected void fill_item( notnull EntityAI item_to_fill, notnull TStringArray item_names_to_put )
	{
		string func_name = "fill_item";
		
		auto container_name = item_to_fill.GetType();
		foreach ( auto idx_attachment, auto item_name_to_put : item_names_to_put )
		{
			g_log.trace( "Item: [" + item_name_to_put + "]; Container: [" + container_name + "]", func_name );
			item_to_fill.GetInventory().CreateInInventory( item_name_to_put );
		}
	}
	
}