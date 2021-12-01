
/*
	*** v1.1.3 ***
	*	BIGINT FOR SAMP!
	*
	*   Creator: HPQ123 (HPQ123#8114 discord)
	*
*/


new bStr[32];																										

#define BigInt:%1; eBit:ByteVar1@%1,eBit:ByteVar2@%1;
#define BT:<%1>	ByteVar1@%1,ByteVar2@%1		

#if !defined IS_IN_RANGE
	#define IS_IN_RANGE(%0,%1,%2) (((%0)-((%1)+cellmin))<((%2)-((%1)+cellmin))) // credits: Y_less
#endif

#define Bytes1024\
	(1000000000)																						
																																
#define formatBytes(%1)\
	_formatBytes(BT:<%1>)									

#define resetBigInt(%1)\
	ByteVar1@%1=ByteVar2@%1=eBit:0										

#define converBytes(%1,%2)\
	extractBytes(BT:<%1>,%2)															
																														
#define addBytes32(%1,%2) whereBytes(BT:<%1>,%2)
stock whereBytes(&eBit:a,&eBit:b,value) {				
	if(value<0) {			
		value=-value;													
		a = a - eBit:(value / Bytes1024);																									
		if(a && b < eBit:Bytes1024) b = eBit:((_:b + Bytes1024) - (value % Bytes1024)), --a; else b = eBit:(_:b - (value % Bytes1024));					
		if(_:b > (Bytes1024-1)) ++a,b -= eBit:Bytes1024;					
	} else a = a + eBit:((_:b + value) / Bytes1024), b = eBit:((_:b + value) % Bytes1024);
	return 1;																												
}

#define bytes32(%1)	_bytes32(BT:<%1>)		
stock _bytes32(eBit:a,eBit:b) {																			                                                                                                                          
	switch(_:a) { 																													                                                                                                                       
		case -1..1: return (_:a * Bytes1024) + _:b; 																                                                                                                                       
		case -2,2: 	return (_:a * Bytes1024) + (_:b < cellmax? (_:b) : cellmax); 								                                                                                                                       
		default: 	return _:a > -1 ? cellmax : -cellmax; 																                                                                                                                          						
	}																														                                                                                                                       
	return 0;																												                                                                                                                       
}			
#define addBytes64(%1,%2) extractBytes(BT:<%1>,#%2)																												                                                                                                                       
stock extractBytes(&eBit:a,&eBit:b,const value[],l=-1,val=0) {                                                                                                                       
	if(value[0] == '-') {                                                                                                                       
		if((l=strmid(bStr, value, 0, 21)) > 10) {                                                                                                                       
			val = strval(bStr[(l = l - 9)]), bStr[l] = '\0';	     
			a = a + eBit:strval(bStr);                                                                                                                                                                                                                                                    
			whereBytes(a, b, _:a>-1?-val:val);   
			return 1;                                                                                     
		}                                                                                                                       
		whereBytes(a, b, _:a>-1?strval(bStr):-val);                                                                                                                   
	} else {                                                                                                                       
		if((l=strmid(bStr, value, 0, 20)) > 9) {                                                                                                                       
			b = b + eBit:strval(bStr[(l = l - 9)]), bStr[l] = '\0';														
			a = a + eBit:strval(bStr);	
			return 1;																			
		}																													
		b = b + eBit:strval(bStr);																			
	}	
	return 1;																													
}																															
stock isBigInt(const bigInt[], i=-1) {																									
	if(bigInt[0]=='-'&&bigInt[1]) ++i;																										
	while(IS_IN_RANGE(bigInt[++i],48,58)) {}																									
	return !bigInt[i];																										
}																															

#define OPByte(%1,%2,%3) bytesOperator(BT:<%1>,#%2,#%3)																						
stock bytesOperator(																							
	eBit:bOP1,eBit:OP1,const _oper[],const _oper2[], 																									
	eBit:bVal=eBit:0, eBit:Val=eBit:0																								
) {																												
	extractBytes(bVal,Val,_oper2);																								
	switch _oper[0]+_oper[1] 																					
	do {																											
		case '='+'=': if(bOP1==bVal&&OP1==Val) return true;														
		case '>'+'=': if((bOP1>bVal||(bOP1==bVal&&OP1>Val))||bOP1==bVal&&OP1==Val) return true;																
		case '<'+'=': if((bVal>bOP1||(bOP1==bVal&&Val>OP1))||bOP1==bVal&&OP1==Val) return true;																
		case '!'+'=': if((bOP1==bVal&&OP1==Val)) return true;																									
		case '<': if(bVal>bOP1||(bOP1==bVal&&Val>OP1)) return true;																													
		case '>': if(bOP1>bVal||(bOP1==bVal&&OP1>Val)) return true;																													
		default: {																								
			#if defined PrintBacktrace																					
				PrintBacktrace();																					
			#else																								
				printf("[BigInt ERROR] Invalid operator '%s'!", _oper)																					
			#endif																								
		}																										
	}																											
	return false;																								
}					
#define valueBigInt(%1)	stringBytes(BT:<%1>)																														
stock stringBytes(eBit:a,eBit:b) {
	if(!a) format(bStr,sizeof bStr,"%d", _:b);
	else format(bStr,sizeof bStr,"%d%09d", _:a, _:b);
	return bStr;																										
}

stock _formatBytes(eBit:a,eBit:b, const chars[] = ".", l=-1) {													
	stringBytes(a,b),l=strlen(bStr);																			
    while((l = l - 3) > 0) strins(bStr, chars, l);																	
    return bStr;																											
}																															
stock formatStrNumber(const int[], const chars[] = ".", l=-1) {																
	bStr[0]='\0',l=strcat(bStr,int);																					
	while((l = l - 3) > 0) strins(bStr, chars, l);																				
    return bStr;																											
}																															
#if defined cache_get_value_name																							
	#define cache_get_value_name_bigint(%1,%2,%3) \
		(resetBigInt(%1),cache_get_value_name(%2,%3,bStr)&&extractBytes(BT:<%1>,bStr))																												
#endif																														
#if defined cache_get_field_content																							
	#define cache_get_field_content_bigint(%1,%2,%3)\
		(resetBigInt(%1),cache_get_field_content(%2,%3,bStr)&&extractBytes(BT:<%1>,bStr))																																																															
#endif 																														
#if defined cache_get_value_name_bigint    && !defined cache_get_value_name
 || defined cache_get_field_content_bigint && !defined cache_get_field_content
	#error The function you are using does not match mysql													
#endif																															