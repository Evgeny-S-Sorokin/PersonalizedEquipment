// Script File
	
enum LogLvl
{
	trace = 0,
	debug,
	info,
	no_log
};

class Alastor_Logger
{
	
	//----------------------------------------------------------------------
	
	LogLvl current_log_lvl;
	
	//----------------------------------------------------------------------
	
	void Alastor_Logger( LogLvl lvl = LogLvl.info )
	{
		current_log_lvl = lvl;
	}
	
	void change_log_level( LogLvl lvl )
	{
		current_log_lvl = lvl;
	}
	
	void trace( string msg, string module = "Not set" )
	{
		if ( current_log_lvl == LogLvl.trace )
		{
			Print( get_current_time() + " | TRACE | " + module + " | " + msg );
		}
		else {}
	}
	
	void debug_info( string msg, string module = "Not set" )
	{
		if ( current_log_lvl <= LogLvl.debug )
		{
			Print( get_current_time() + " | DEBUG | " + module + " | " + msg );
		}
		else {}
	}
	
	void info( string msg, string module = "Not set" )
	{
		if ( current_log_lvl <= LogLvl.info )
		{
			Print( get_current_time() + " | INFO  | " + module + " | " + msg );
		}
		else {}
	}
	
	void error( string msg, string module = "Not set" )
	{
		if ( current_log_lvl <= LogLvl.info )
		{
			Print( get_current_time() + " | ERROR | " + module + " | " + msg );
		}
		else {}
	}
	
	//----------------------------------------------------------------------	
	
	private string get_current_time()
	{
		int year, month, day, hour, minute, second;
			
		GetYearMonthDay( year, month, day );		
		GetHourMinuteSecond( hour, minute, second );
		
		string date = day.ToStringLen( 2 ) + "." + month.ToStringLen( 2 ) + "." + year.ToStringLen( 2 );
		string time = hour.ToStringLen( 2 ) + ":" + minute.ToStringLen( 2 ) + ":" + second.ToStringLen( 2 );
		
		return  ( date + " | " + time );
	}
	
	//----------------------------------------------------------------------	
	
}

ref Alastor_Logger g_log = new ref Alastor_Logger( LogLvl.debug );