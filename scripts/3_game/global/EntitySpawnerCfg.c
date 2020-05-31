// Script File

class EntitySpawnerCfg
{	
	//-file info------------------------------------
	static const string file_dir	= "$profile:EntitySpawnerCfg\\";
	static const string file_name 	= "EntitySpawner.json";
	static const string file_path 	= file_dir + file_name;
	
	//-EntitySpawner parametrs----------------------
	protected string 	_container_name 		= "Barrel_Yellow";
	protected int		_recursion_depth_max 	= 10;
	protected int		_entity_spawn_delay 	= 120;
	protected int		_entity_despawn_delay 	= 300;
	protected bool		_is_entity_persistent	= false;
	
	//-Constructor----------------------------------
	void EntitySpawnerCfg()
	{
		string func_name = "EntitySpawnerCfg";
		if ( GetGame().IsClient() )
		{
			return;
		}
		else {}
		
		g_log.info( "Reading config [" + file_path + "]", func_name );
		if ( !FileExist( file_dir ) )
		{
			g_log.info( "No directory [" + file_dir + "]. Creating one!", func_name );
			MakeDirectory( file_dir );
		}
		else {}
		
		if ( !FileExist( file_path ) )
		{
			g_log.info( "No config file [" + file_name + "]. Creating one!", func_name );
			save();
		}
		else {}
		
		load();
	}
	
	//-getters-------------------------------------
	string get_container_name()
	{
		return _container_name;
	}
	int get_entity_spawn_delay()
	{
		return _entity_spawn_delay;
	}
	int get_entity_despawn_delay()
	{
		return _entity_despawn_delay;
	}
	int get_recursion_depth_max()
	{
		return _recursion_depth_max;
	}
	bool get_entity_persistence()
	{
		return _is_entity_persistent;
	}
	
	//-load cfg from file--------------------------
	protected bool load()
	{
		string func_name = "load";
		if ( FileExist( file_path ) )
		{
			g_log.info( "Loading config from [" + file_path + "]", func_name );
			JsonFileLoader< EntitySpawnerCfg >.JsonLoadFile( file_path, this );
			return true;
		}
		else 
		{
			return false;
		}
	}
	
	//-save cfg to file---------------------------
	protected void save()
	{
		JsonFileLoader< EntitySpawnerCfg >.JsonSaveFile( file_path, this );
	}
}