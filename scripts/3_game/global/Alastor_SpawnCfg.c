// Script File

class Alastor_SpawnCfg
{
		
	//----------------------------------------------------------------------
	//-file info------------------------------------
	static const string mod_dir	 = "$profile:PersonalizedEquipment\\";
	static const string file_dir = mod_dir + "SpawnCfg\\";

	//-Player parametrs----------------------
	private float _x = 10875.80;
	private float _y = 6;
	private float _z = 2518.90;
	
	//----------------------------------------------------------------------
	
	void Alastor_SpawnCfg( string spawn_type )
	{
		if ( GetGame().IsClient() )
		{
			return;
		}
		else {}
		
		string func_name = "Alastor_SpawnCfg";
		string file_name;
		string file_path;
		
		g_log.info( "Checking mod directory [" + mod_dir + "]", func_name );
		if ( !FileExist( mod_dir ) )
		{
			g_log.error( "No directory [" + mod_dir + "]. Creating one!", func_name );
			MakeDirectory( mod_dir );
		}
		else {}
		
		g_log.info( "Checking file directory [" + file_dir + "]", func_name );
		if ( !FileExist( file_dir ) )
		{
			g_log.error( "No directory [" + file_dir + "]. Creating one!", func_name );
			MakeDirectory( file_dir );		
		}
		else {}
		
		if ( ( spawn_type != "" ) )
		{ }
		else 
		{
			g_log.error( "Failed to get player's spawn type!", func_name );
			spawn_type = "Default";
		}
			
		file_name = spawn_type + ".json";
		file_path = file_dir + file_name;
		
		g_log.info( "Reading config [" + file_path + "]", func_name );
		if ( !FileExist( file_path ) )
		{
			g_log.error( "No file [" + file_path + "]. Creating one!", func_name );
			save( file_path );
		}
		else {}
		
		load( file_path );
	}
	
	// Getters
	int get_x()
	{
		return _x;
	}
	int get_y()
	{
		return _y;
	}
	int get_z()
	{
		return _z;
	}
	
	//----------------------------------------------------------------------
	
	//-load cfg from file--------------------------
	protected bool load( string file_path )
	{
		string func_name = "load              ";
		
		if ( FileExist( file_path ) )
		{
			g_log.info( "Loading config from [" + file_path + "]", func_name );
			JsonFileLoader< Alastor_SpawnCfg >.JsonLoadFile( file_path, this );
			return true;
		}
		else 
		{
			return false;
		}
	}
	
	//-save cfg to file---------------------------
	protected void save( string file_path )
	{
		JsonFileLoader< Alastor_SpawnCfg >.JsonSaveFile( file_path, this );
	}
	
	//----------------------------------------------------------------------

}