#ifndef _QUERY_H_
#define __DbStuff
#define _QUERY_H_

#include <sql.h>
#include <sqlext.h>

struct QUERY_BINDINFO
{
	SQLSMALLINT targetType;
	SQLPOINTER	targetValue;
	SQLINTEGER	bufferLength;
	SQLINTEGER*	strLen_or_Ind;
};

class CQuery
{
public:
//	char *DBName, *DBId, *DBPass;	
	char DBName[256];
	char DBId[256];
	char DBPass[256];
#ifdef __DbStuff
	enum class SqlDatabase { ACCOUNT, CHARACTER, RANKING, LOGGING, BACKEND, ITEM, SITE, WORLD };
	SqlDatabase m_dbType;
#endif 

	// �ִ� �÷���, BLOB ����� ����, NULL �ʵ尪
	enum { MAXCOL=256, MAX_COLNAME = 128, BLOBBATCH=10000, CQUERYNULL=-100, CQUERYEOF=-101, 
		CQUERYNOCOL=-102, CQUERYERROR=-103
		, MAXTBL = MAX_PATH
		, MAX_FULL_COL = MAXTBL+1+MAXCOL};			//1�� '.'
private:
	SQLHENV hEnv;							// ȯ�� �ڵ�
	SQLHDBC hDbc;							// ���� �ڵ�
	char*	Col[MAXCOL];					// ���ε��� �÷� ����

	int FindCol(char *name);				// �÷��� �̸����κ��� ��ȣ�� ã���ش�.


	char					szTable[ MAXTBL ];

	SQLUSMALLINT	ParameterNumber;
	SQLINTEGER		ValueLength;

//public:
//	void					SetTable( const char * szTableName );

public:
	SQLHSTMT hStmt;							// ���� �ڵ�. ���� ����� ���� �����Ƿ� public���� ����
	SQLSMALLINT nCol;						// �÷� ����
	SQLCHAR ColName[MAXCOL][MAX_COLNAME];			// �÷��� �̸���
	SQLINTEGER lCol[MAXCOL];				// �÷��� ����/���� ����

	CQuery();								// ������
	~CQuery();								// �ı���:���� �ڵ��� �����Ѵ�.

	void PrintDiag( LPCTSTR szSQL, SQLSMALLINT type = SQL_HANDLE_DBC );						// ���� ���� ���

#ifdef __DbStuff
	bool Connect(SqlDatabase dbType);
#else
	BOOL Connect(int Type, char *ConStr, char *UID=NULL, const char *PWD=NULL);	// ������ �ҽ��� �����Ѵ�.
#endif
	void DisConnect();						// ������ �ҽ� ������ ���´�
	BOOL Exec(LPCTSTR szSQL);				// SQL���� �����Ѵ�.
	BOOL PrepareFetch();

	BOOL	PrepareQuery( const TCHAR * szQuery );

	BOOL	Execute( LPCTSTR lpszFormat, ... );

	int ExecGetInt(LPCTSTR szSQL);			// SQL���� �����ϰ� ù��° �÷��� ���� ����
	void ExecGetStr(LPCTSTR szSQL, char *buf);		// SQL���� �����ϰ� ù��° �÷��� ���ڿ� ����
	BOOL Fetch();						// �� �� ��������
	void Clear();							// Ŀ�� ���� �� �� ���ε�
	void ClearParam();						// �Ķ��� �ʱ�ȭ



	bool					IsValidColumn( char *szName );


	int						GetInt(int nCol);					// ������ �÷� �б�
	int						GetInt(char *sCol);					// ������ �÷� �б�

	__int64					GetInt64( int nCol );
	__int64					GetInt64( char* sCol );

	EXPINTEGER				GetExpInteger( int nCol );
	EXPINTEGER				GetExpInteger(	char* sCol );
	SERIALNUMBER			GetSerialNumber( int nCol );
	SERIALNUMBER			GetSerialNumber( char* sCol );

	float					GetFloat(int nCol);					// �Ǽ��� �÷� �б�
	float					GetFloat(char *sCol);				// �Ǽ��� �÷� �б�
	char					GetChar(int nCol);					// �Ǽ��� �÷� �б�
	char					GetChar(char *sCol);				// �Ǽ��� �÷� �б�
	void					GetStr(int nCol, char *buf, size_t cchBuf);		// ���ڿ��� �÷� �б�
	void					GetStr(char *sCol, char *buf, size_t cchBuf);		// ���ڿ��� �÷� �б�

	//---------------------------------------------------------------------------------------------
	void					makeFullColName( char * szFullColName, const size_t uCCh, const char * szCol );
		

	int						GetIntFromTbl(char *sCol);					// ������ �÷� �б�
	__int64					GetInt64FromTbl( char* sCol );
	EXPINTEGER				GetExpIntegerFromTbl( char* sCol );
	SERIALNUMBER			GetSerialNumberFromTbl( char* sCol );
	float					GetFloatFromTbl(char *sCol);				// �Ǽ��� �÷� �б�
	char					GetCharFromTbl(char *sCol);				// �Ǽ��� �÷� �б�
	void					GetStrFromTbl(char *sCol, char *buf, size_t cchBuf);	// ���ڿ��� �÷� �б�


	int ReadBlob(LPCTSTR szSQL, void *buf);
	void WriteBlob(LPCTSTR szSQL, void *buf, int size);

	BOOL	BindParameterByte( SQLSMALLINT ParamType, SQLPOINTER ParameterValuePtr );

	BOOL	BindParameterShort( SQLSMALLINT ParamType, SQLPOINTER ParameterValuePtr );
	BOOL	BindParameterUShort( SQLSMALLINT ParamType, SQLPOINTER ParameterValuePtr );

	BOOL	BindParameterInt( SQLSMALLINT ParamType, SQLPOINTER ParameterValuePtr );
	BOOL	BindParameterUInt( SQLSMALLINT ParamType, SQLPOINTER ParameterValuePtr );

	BOOL	BindParameterInt64( SQLSMALLINT ParamType, SQLPOINTER ParameterValuePtr );
	BOOL	BindParameterUInt64( SQLSMALLINT ParamType, SQLPOINTER ParameterValuePtr );

	BOOL	BindParameterFloat( SQLSMALLINT ParamType, SQLPOINTER ParameterValuePtr );

	BOOL	BindParameterChar( SQLSMALLINT ParamType, SQLUINTEGER ColumnSize, SQLPOINTER ParameterValuePtr );
	BOOL	BindParameterVarChar( SQLSMALLINT ParamType, SQLUINTEGER ColumnSize, SQLPOINTER ParameterValuePtr );


// 	BOOL BindParameter(SQLUSMALLINT parameterNumber,
//                            SQLSMALLINT inputOutputType,
//                            SQLSMALLINT valueType,
//                            SQLSMALLINT parameterType,
//                            SQLUINTEGER columnSize,
//                            SQLSMALLINT decimalDigits,
//                            SQLPOINTER  parameterValuePtr,
//                            SQLINTEGER bufferLength,
//                            SQLINTEGER *strLen_or_IndPtr);
	
	BOOL MoreResults( void );

	void WriteLogFile(const char *strLog,...);
	static BOOL EnableConnectionPooling();


public:

	struct FLColumnInfo
	{
		enum				{		DB_STR_MAX = 31, 	};
		//const size_t		

		char				szCatalog[ DB_STR_MAX ];		
		char				szSchema[ DB_STR_MAX ];			
		char				szTableName[ DB_STR_MAX ];		
		char				szColumnName[ DB_STR_MAX ];		
		SQLSMALLINT			shDataType;				
		char				szDataTypeName[ DB_STR_MAX ];	
		SQLINTEGER			nColSize;					
		SQLINTEGER			nBufferLen;				
		SQLSMALLINT			shDecimalDigits;			
		SQLSMALLINT			shNumPrecRadix;			
		SQLSMALLINT			shNullAble;				
		char				szRemark[ DB_STR_MAX ];			
		char				szColumnDefault[ DB_STR_MAX ];	
		SQLSMALLINT			shSqlDataType;			
		SQLSMALLINT			shSqlDataTypeSub;		
		SQLSMALLINT			shCharOctetLen;			
		SQLSMALLINT			shOrdinalPosition;		
		char				szIsNullAble[ DB_STR_MAX ];		
	};


	typedef					std::vector< FLColumnInfo >		ColumnInfoVec;
	BOOL					GetColumns( SQLCHAR * szTable, ColumnInfoVec & o_vecColumnInfo );
};
// TODO: ��� �и� 
// ��ȣȭ�� ��ū�� �ص��ؼ� �н������ ��´�.
// ��: ��ū - 3A08DB22
extern BOOL GetPWDFromToken( const char* szToken, char* szPWD );
#endif

