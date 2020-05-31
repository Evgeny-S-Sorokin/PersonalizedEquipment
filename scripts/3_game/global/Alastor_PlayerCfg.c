// Script File

class Alastor_PlayerCfg
{
	
	//----------------------------------------------------------------------
	//-file info------------------------------------
	static const string mod_dir	 = "$profile:PersonalizedEquipment\\";
	static const string file_dir = mod_dir + "PlayerCfg\\";

	//-Player parametrs----------------------
	private string _spawn_type 		= "Default";
	private string _loadout_type 	= "Default";
	private string _face			= "SurvivorM_Peter";
	
	//----------------------------------------------------------------------
	
	void Alastor_PlayerCfg( PlayerIdentity identity )
	{
		if ( GetGame().IsClient() )
		{
			return;
		}
		else {}
		
		string func_name = "Alastor_PlayerCfg";
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
		
		string Steam64_ID = identity.GetPlainId();
		if ( ( Steam64_ID != "" ) )
		{
			file_name = Steam64_ID + ".json";
			file_path = file_dir + file_name;	
		}
		else 
		{
			g_log.error( "Failed to get player's Steam64_ID!", func_name );
			return;
		}
		
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
	string get_spawn_type()
	{
		return _spawn_type;
	}
	string get_loadout_type()
	{
		return _loadout_type;
	}
	string get_face()
	{
		return _face;
	}
	
	//----------------------------------------------------------------------
	
	//-load cfg from file--------------------------
	protected bool load( string file_path )
	{
		string func_name = "load              ";
		
		if ( FileExist( file_path ) )
		{
			g_log.info( "Loading config from [" + file_path + "]", func_name );
			JsonFileLoader< Alastor_PlayerCfg >.JsonLoadFile( file_path, this );
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
		JsonFileLoader< Alastor_PlayerCfg >.JsonSaveFile( file_path, this );
	}
	
	//----------------------------------------------------------------------
	
}