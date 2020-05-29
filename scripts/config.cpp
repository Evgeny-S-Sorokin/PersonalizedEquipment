class CfgPatches
{
	class PersonalizedEquipment
	{
		units[]				= {};
		weapons[]			= {};
		requiredVersion		= 0.1;
		requiredAddons[]	= { "DZ_Data" };
	};
};

class CfgMods
{
	class PersonalizedEquipment
	{
	    type 			= "mod";
		name 			= "PersonalizedEquipment";
		author 			= "Alastor";
		authorID 		= "76561198052045611";
	    dependencies[] 	= { "Game", "World", "Mission" };
		
	    class defs
	    {

			class gameScriptModule
            {
                value	= "";
                files[] = { "PersonalizedEquipment/scripts/3_game" };
            };
			
			class worldScriptModule		
            {
                value	= "";
                files[] = { "PersonalizedEquipment/scripts/4_world" };
            };
			
			class missionScriptModule
			{
				value	= "";
				files[] = { "PersonalizedEquipment/scripts/5_mission" };
			}
        };
    };
};