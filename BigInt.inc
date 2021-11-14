
						///////////////////////////////////////////////////////////////////
						///																///
						///																///
						///					 BigInt for SA-MP v1.1.2					///
						///						Creator: HPQ123							///
						///				  Contact Discord: HPQ123#8114					///
						///																///
						///																///
						///////////////////////////////////////////////////////////////////


//////////////////////////////////////// ** Defined ** ////////////////////////////////////////////////////////////////////////////
static int_str[32];																												///
																																///
#define bigInt:%1<> 		 						Bit64:_int@%1,Bit64:_bigInt@%1   											///
#define _64bit(%0,%1,%2) 							(((%0)-((%1)+cellmin))<((%2)-((%1)+cellmin))) 								///
#define _KKK 										(1000000000)																///
#define M32bit										(2147483647)																///
#define INVALID_BIGINT								(Bit64:0)																	///
																																///
#define OP64(%1,%2,%3)								check64Operator(_bigInt@%1,_int@%1,#%2,#%3)									///
#define giveBigInt(%1,%2)							extractBigInt(_bigInt@%1,_int@%1,#%2##)										///
#define convert64to32(%1)							_64to32(_bigInt@%1,_int@%1)													///
#define add32Bit(%1,%2)								_selectInt(_bigInt@%1,_int@%1,%2)											///
#define formatBigInt(%1)							_fmt64bit(_bigInt@%1,_int@%1)												///
#define resetBigInt(%1)								_resetInt(_bigInt@%1,_int@%1)												///
#define string_to_bigInt(%1,%2)						extractBigInt(_bigInt@%1,_int@%1,%2)										///
#define returnBigInt(%1)							_return64bit(_bigInt@%1,_int@%1)											///
																																///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////// ** Main functions ** ///////////////////////////////////////////////////////////////////////
																																///
stock _selectInt(&Bit64:mInt,&Bit64:Int,val) 		return val<0?_rmvInt(mInt,Int,-val):_addInt(mInt,Int,val);					///
stock _addInt(&Bit64:mInt,&Bit64:Int,val)			return mInt+=Bit64:((_:Int+val)/_KKK),Int=Bit64:((_:Int+val)%_KKK),1;		///
stock _resetInt(&Bit64:mInt,&Bit64:int,r_value=0) 	return mInt=int=Bit64:r_value,1;											///
stock _rmvInt(&Bit64:mInt,&Bit64:Int,val) {																						///
	mInt-=Bit64:(val/_KKK);																										///
	if mInt&&Int<Bit64:_KKK *then Int=Bit64:((_:Int+_KKK)-(val%_KKK)),--mInt; else Int=Bit64:(_:Int-(val%_KKK));				///
	if _:Int>(_KKK-1) *then ++mInt,Int-=Bit64:_KKK;																				///
	return 1;																													///
}																																///
stock _64to32(Bit64:_bigInt@mInt,Bit64:_int@Int) {																				///                                                                                                                                   
	switch _:_bigInt@mInt 																										///                                                                                                                                  
	do { 																													    ///                                                                                                                               
		case -1..1: return (_:_bigInt@mInt*_KKK)+_:_int@Int; 																    ///                                                                                                                               
		case -2,2: 	return (_:_bigInt@mInt*_KKK)+(_:_int@Int<M32bit? (_:_int@Int) : M32bit); 								    ///                                                                                                                               
		default: 	return _:_bigInt@mInt>-1?M32bit:-M32bit; 																	///                                                                                                                                   						
	}																														    ///                                                                                                                               
	return 0;																												    ///                                                                                                                               
}																															    ///                                                                                                                               
stock extractBigInt(&Bit64:ret_mInt,&Bit64:ret_int,const _bigInt[],l=-1,val=0) {                                                ///                                                                                   
	if(_bigInt[0] == '-') {                                                                                                     ///                              
		if((l=strmid(int_str,_bigInt,0,21))>10) {                                                                               ///                                                    
			val = strval(int_str[(l=l-9)]),int_str[l]='\0';	                                                                    ///                                                               
			ret_mInt = ret_mInt+Bit64:strval(int_str);                                                                          ///                                                         
			_rmvInt(ret_mInt,ret_int,val);                                                                                      ///                                             
		}                                                                                                                       ///            
		else _rmvInt(ret_mInt,ret_int,-strval(int_str));                                                                        ///                                                           
	} else {                                                                                                                    ///               
		if((l=strmid(int_str,_bigInt,0,20))>9) {                                                                                ///                                                   
			ret_int+=Bit64:strval(int_str[(l=l-9)]),int_str[l]='\0';															///
			ret_mInt+=Bit64:strval(int_str);																					///
		}																														///
		else ret_int+=Bit64:strval(int_str);																					///
	}																															///
}																																///
stock isBigInt(const bigInt[], i=-1) {																							///						
	if bigInt[0]=='-'&&bigInt[1] *then ++i;																						///							
	while(_64bit(bigInt[++i],48,58)) {}																							///						
	return !bigInt[i];																											///		
}																																///
																																///
stock check64Operator(																											///		
	Bit64:bOP1,Bit64:OP1,const _oper[],const _oper2[], 																			///														
	Bit64:bVal=INVALID_BIGINT, Bit64:Val=INVALID_BIGINT																			///													
) {																																///
	extractBigInt(bVal,Val,_oper2);																								///								
	switch _oper[0]+_oper[1] 																									///
	do {																														///					
		case '='+'=': if(bOP1==bVal&&OP1==Val) return true;																		///
		case '>'+'=': if((bOP1>bVal||(bOP1==bVal&&OP1>Val))||bOP1==bVal&&OP1==Val) return true;									///															
		case '<'+'=': if((bVal>bOP1||(bOP1==bVal&&Val>OP1))||bOP1==bVal&&OP1==Val) return true;									///															
		case '!'+'=': if((bOP1==bVal&&OP1==Val)) return true;																	///																
		case '<': if(bVal>bOP1||(bOP1==bVal&&Val>OP1)) return true;																///																					
		case '>': if(bOP1>bVal||(bOP1==bVal&&OP1>Val)) return true;																///																					
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
stock _return64bit(Bit64:mInt,Bit64:_int) {																						///
	if !mInt *then format(int_str,sizeof int_str,"%d", _:_int); else format(int_str,sizeof int_str,"%d%09d", _:mInt, _:_int);	///														
	return int_str;																												///
}																																///
stock _fmt64bit(Bit64:mInt,Bit64:_int, const chars[] = ".", length=-1) {														///			
	_return64bit(mInt,_int),length=strlen(int_str);																				///
    while((length-=3)>0) strins(int_str, chars, length);																		///
    return int_str;																												///
}																																///
stock formatStrNumber(const int[], const chars[] = ".", l=-1) {																	///		
	int_str[0]='\0',l=strcat(int_str,int);																						///
	while((l=l-3)>0) strins(int_str, chars, l);																					///
    return int_str;																												///
}																																///
#if defined cache_get_value_name																								///
	#define cache_get_value_name_bigint(%1,%2,%3) _loading_data(_bigInt@%1,_int@%1,%2,%3)										///						
																																///
	stock _loading_data(&Bit64:mInt,&Bit64:Int,row,const column[]) {															///		
		new data[20 + 1]; mInt=Int=INVALID_BIGINT;																				///
		cache_get_value_name(row,column,data);																					///
		extractBigInt(mInt,Int,data);																							///
		return true;																											///
	}																															///
#endif																															///
#if defined cache_get_field_content																								///
	#define cache_get_field_content_bigint(%1,%2,%3) _loading_data(_bigInt@%1,_int@%1,%2,%3)									///							
																																///
	stock _loading_data(&Bit64:mInt,&Bit64:Int,row,const column[]) {															///		
		new data[20 + 1]; mInt=Int=INVALID_BIGINT;																				///
		cache_get_field_content(row,column,data);																				///
		extractBigInt(mInt,Int,data);																							///
		return true;																											///
	}																															///
#endif 																															///
#if !defined cache_get_field_content && !defined cache_get_value_name 															///
	#error The function you are using does not match mysql																		
#endif																															///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
