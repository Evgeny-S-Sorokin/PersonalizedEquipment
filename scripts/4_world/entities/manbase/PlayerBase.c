// Script File

modded class PlayerBase
{
	
	//-----------------------------------------------------------------------------------------
	
	override void EEKilled( Object killer )
	{
		super.EEKilled( killer );
		
		EntitySpawner.push_back_corpse( this );
	}
	
	//-----------------------------------------------------------------------------------------
	
	void set_spawn_type( string spawn_type )
	{
		_spawn_type = spawn_type;
	}
	void set_loadout_type( string loadout_type )
	{
		_loadout_type = loadout_type;
	}
	
	string get_spawn_type()
	{
		return _spawn_type;
	}
	string get_loadout_type()
	{
		return _loadout_type;
	}
	
	//-----------------------------------------------------------------------------------------
	
	protected string _spawn_type;
	protected string _loadout_type;
	
	//-----------------------------------------------------------------------------------------
	
}