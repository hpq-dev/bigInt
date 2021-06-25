
						///////////////////////////////////////////////////////////////////
						///																///
						///																///
						///					 BigInt for SA-MP v1.1.1					///
						///						Creator: HPQ123							///
						///				  Contact Discord: HPQ123#8114					///
						///																///
						///																///
						///////////////////////////////////////////////////////////////////


//////////////////////////////////////// ** Defined ** ////////////////////////////////////////////////////////////////////////////
static int_str[32];																												///
																																///
#define _32::									int@																			///
#define _64::									bigInt@																			///
#define new_BigInt::<%1>						new bigInt:_32::%1,bigInt:_64::%1;												///
#define _64bit(%0,%1,%2) 						(((%0)-((%1)+cellmin))<((%2)-((%1)+cellmin))) 									///
#define _KKK 									(1000000000)																	///
#define M32bit									(2147483647)																	///
#define INVALID_BIGINT							(bigInt:0)																		///
																																///
#define OP64(%1,%2,%3)							check64Operator(_64::%1,_32::%1,#%2,#%3)										///
#define giveBigInt(%1,%2)						extractBigInt(_64::%1,_32::%1,#%2##)											///
#define convert64to32(%1)						_64to32(_64::%1,_32::%1)														///
#define add32Bit(%1,%2)							_selectInt(_64::%1,_32::%1,%2)													///
#define formatBigInt(%1)						_fmt64bit(_64::%1,_32::%1)														///
#define resetBigInt(%1)							_resetInt(_64::%1,_32::%1)														///
#define string_to_bigInt(%1,%2)					extractBigInt(_64::%1,_32::%1,%2)												///
#define returnBigInt(%1)						_return64bit(_64::%1,_32::%1)													///
																																///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////// ** Main functions ** ///////////////////////////////////////////////////////////////////////
																																///
stock _selectInt(&bigInt:mInt,&bigInt:Int,val) 		return val<0?_rmvInt(mInt,Int,-val):_addInt(mInt,Int,val);					///
stock _addInt(&bigInt:mInt,&bigInt:Int,val)			return mInt+=bigInt:((_:Int+val)/_KKK),Int=bigInt:((_:Int+val)%_KKK),1;		///
stock _resetInt(&bigInt:mInt,&bigInt:int,r_value=0) return mInt=int=bigInt:r_value,1;											///
stock _rmvInt(&bigInt:mInt,&bigInt:Int,val) {																					///
	mInt-=bigInt:(val/_KKK);																									///
	if mInt&&Int<bigInt:_KKK *then Int=bigInt:((_:Int+_KKK)-(val%_KKK)),--mInt; else Int=bigInt:(_:Int-(val%_KKK));				///
	if _:Int>(_KKK-1) *then ++mInt,Int-=bigInt:_KKK;																			///
	return 1;																													///
}																																///
stock _64to32(bigInt:_64::mInt,bigInt:_32::Int) {																				///
	switch _64::mInt do { 																										///
		case 0,1: 	return (_64::mInt*bigInt:_KKK)+_32::Int; 																	///
		case 2: 	return (_64::mInt*bigInt:_KKK)+(_32::Int<bigInt:M32bit? _32::Int : bigInt:M32bit); 							///
		default: 	return M32bit; 																								///
	}																															///
	return 0;																													///
}																																///
stock extractBigInt(&bigInt:ret_mInt,&bigInt:ret_int,const _bigInt[],l=-1,x=-1) {												///
	if((l=strmid(int_str,_bigInt,0,20+(x=_:_bigInt[0]=='-')))>9) {																///
		ret_int+=bigInt:strval(int_str[(x=(l-9)+x)]),int_str[x]='\0';															///
		ret_mInt+=bigInt:strval(int_str);																						///
		return;																													///
	}																															///
	ret_int+=bigInt:strval(int_str);																							///
}																																///
stock isBigInt(const bigInt[], i=-1) {																							///						
	if bigInt[0]=='-'&&bigInt[1] *then ++i;																						///							
	while(_64bit(bigInt[++i],48,58)) {}																							///						
	return !bigInt[i];																											///		
}																																///
stock check64Operator(																											///		
	bigInt:_64::oper1,bigInt:_32::oper1,const _oper[],const _oper2[], 															///														
	bigInt:_64::val=INVALID_BIGINT, bigInt:_32::val=INVALID_BIGINT																///													
) {																																///
	extractBigInt(_64::val,_32::val,_oper2);																					///								
	switch _oper[0]+_oper[1] do {																								///					
		case '='+'=': 																											///		
			if _64::oper1==_64::val&&_32::oper1==_32::val *then return true;													///																
																																///
		case '>'+'=': 																											///		
			if((_64::oper1>_64::val||(_64::oper1==_64::val&&_32::oper1>_32::val))||												///																	
				_64::oper1==_64::val&&_32::oper1==_32::val) return true;														///															
																																///
		case '<'+'=': 																											///		
			if((_64::val>_64::oper1||(_64::oper1==_64::val&&_32::val>_32::oper1))||												///																	
				_64::oper1==_64::val&&_32::oper1==_32::val) return true;														///															
																																///
		case '!'+'=': 																											///		
			if !(_64::oper1==_64::val&&_32::oper1==_32::val) *then return true;													///																
																																///
		case '<': 																												///	
			if _64::val>_64::oper1||(_64::oper1==_64::val&&_32::val>_32::oper1) *then return true;								///																					
																																///
		case '>': 																												///	
			if _64::oper1>_64::val||(_64::oper1==_64::val&&_32::oper1>_32::val) *then return true;								///																					
																																///
		default: {																												///	
			#if defined PrintBacktrace																							///						
				PrintBacktrace();																								///					
			#else																												///	
				printf("[BigInt ERROR] Invalid operator '%s'!", _oper)															///														
			#endif																												///	
		}																														///
	}																															///
	return false;																												///	
}																																///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////// ** Other Functions ** ////////////////////////////////////////////////////////////////////
																																///
stock _return64bit(bigInt:mInt,bigInt:_int) {																					///
	if !mInt *then format(int_str,sizeof int_str,"%d", _int); else format(int_str,sizeof int_str,"%d%09d", mInt, _int);			///														
	return int_str;																												///
}																																///
stock _fmt64bit(bigInt:mInt,bigInt:_int, const chars[] = ".", length=-1) {														///			
	_return64bit(mInt,_int),length=strlen(int_str);																				///
    while((length-=3)>0) strins(int_str, chars, length);																		///
    return int_str;																												///
}																																///
stock formatStrNumber(const int[], const chars[] = ".", length=-1) {															///		
	int_str[0]='\0',length=strcat(int_str,int);																					///
	while((length-=3)>0) strins(int_str, chars, length);																		///
    return int_str;																												///
}																																///
#if defined cache_get_value_name																								///
	#define cache_get_value_name_bigint(%1,%2,%3) _loading_data(_64::%1,_32::%1,%2,%3)											///						
																																///
	stock _loading_data(&bigInt:mInt,&bigInt:Int,row,const column[]) {															///		
		new data[20 + 1]; mInt=Int=INVALID_BIGINT;																				///
		cache_get_value_name(row,column,data);																					///
		extractBigInt(mInt,Int,data);																							///
		return true;																											///
	}																															///
#else																															///
#if defined cache_get_field_content																								///
	#define cache_get_field_content_bigint(%1,%2,%3) _loading_data(_64::%1,_32::%1,%2,%3)										///							
																																///
	stock _loading_data(&bigInt:mInt,&bigInt:Int,row,const column[]) {															///		
		new data[20 + 1]; mInt=Int=INVALID_BIGINT;																				///
		cache_get_value_name(row,column,data);																					///
		extractBigInt(mInt,Int,data);																							///
		return true;																											///
	}																															///
#else																															///
	#error The function you are using does not match mysql																		
#endif																															///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////