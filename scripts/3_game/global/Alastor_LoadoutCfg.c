// Script File

class Alastor_LoadoutCfg
{
	
	//----------------------------------------------------------------------
	//-file info------------------------------------
	static const string mod_dir	 = "$profile:PersonalizedEquipment\\";
	static const string file_dir = mod_dir + "LoadoutCfg\\";
	
	/*       */
	/*private*/  	string 			slot_mask;	
	/*private*/  	string 			slot_eyewear;
	/*       */
	/*private*/  	string 			slot_headgear;
	/*private*/ ref array< string > slot_headgear_attachments 	= new ref array< string >;
	/*private*/ ref array< string > slot_headgear_cargo 		= new ref array< string >;
	/*       */
	/*private*/  	string 			slot_shoulder_1;
	/*private*/ ref array< string > slot_shoulder_1_attachments = new ref array< string >;
	/*private*/ ref array< string > slot_shoulder_1_cargo 		= new ref array< string >;
	/*       */
	/*private*/  	string 			slot_shoulder_2;
	/*private*/ ref array< string > slot_shoulder_2_attachments = new ref array< string >;
	/*private*/ ref array< string > slot_shoulder_2_cargo 		= new ref array< string >;
	/*       */
	/*private*/  	string 			slot_gloves;
	/*       */
	/*private*/  	string 			slot_hands;
	/*private*/ ref array< string > slot_hands_attachments 	= new ref array< string >;
	/*private*/ ref array< string > slot_hands_cargo 		= new ref array< string >;
	/*       */
	/*private*/ 	string			slot_armband;
	/*private*/ ref array< string > slot_armband_attachments 	= new ref array< string >;
	/*private*/ ref array< string > slot_armband_cargo 			= new ref array< string >;
	/*       */
	/*private*/  	string 			slot_vest;
	/*private*/ ref array< string > slot_vest_attachments 	= new ref array< string >;
	/*private*/ ref array< string > slot_vest_cargo		 	= new ref array< string >;
	/*       */
	/*private*/  	string 			slot_body;
	/*private*/ ref array< string > slot_body_attachments 	= new ref array< string >;
	/*private*/ ref array< string > slot_body_cargo 		= new ref array< string >;
	/*       */
	/*private*/  	string 			slot_back;
	/*private*/ ref array< string > slot_back_attachments 	= new ref array< string >;
	/*private*/ ref array< string > slot_back_cargo 		= new ref array< string >;
	/*       */
	/*private*/  	string 			slot_hips;
	/*private*/ ref array< string > slot_hips_attachments 	= new ref array< string >;
	/*private*/ ref array< string > slot_hips_cargo 		= new ref array< string >;
	/*       */
	/*private*/  	string 			slot_legs;
	/*private*/ ref array< string > slot_legs_attachments 	= new ref array< string >;
	/*private*/ ref array< string > slot_legs_cargo 		= new ref array< string >;
	/*       */
	/*private*/  	string 			slot_feet;
	/*private*/ ref array< string > slot_feet_attachments 	= new ref array< string >;
	/*private*/ ref array< string > slot_feet_cargo 		= new ref array< string >;
	
	//----------------------------------------------------------------------
	
		
	//----------------------------------------------------------------------

	void Alastor_LoadoutCfg( string loadout_type )
	{
		if ( GetGame().IsClient() )
		{
			return;
		}
		else {}
		
		string func_name = "Alastor_LoadoutCfg";
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
		
		if ( ( loadout_type != "" ) )
		{ }
		else 
		{
			g_log.error( "Failed to get player's loadout!", func_name );
			loadout_type = "Default";
		}
			
		file_name = loadout_type + ".json";
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
	
	//----------------------------------------------------------------------
	
	//-load cfg from file--------------------------
	protected bool load( string file_path )
	{
		string func_name = "load              ";
		
		if ( FileExist( file_path ) )
		{
			JsonFileLoader< Alastor_LoadoutCfg >.JsonLoadFile( file_path, this );
			g_log.info( "Loading config from [" + file_path + "]", func_name );
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
		JsonFileLoader< Alastor_LoadoutCfg >.JsonSaveFile( file_path, this );
	}
	
	//----------------------------------------------------------------------
	
}