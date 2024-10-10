/*
 * MOORE SPECIFICATIONS
 *
 * Copyright (c) 2024; ALL RIGHTS RESERVED!
 *
 * THIS DOCUMENT AND ANY DERIVITIVE OR OTHERWISE RELATED DOCUMENTS ARE
 * BOUND BY THE LISCENCE AGREEMENT FOR CODE OF UNQUESTIONALBLE COMPLIANCE
 *
 * A COPY OF THIS LISCENCE IS PROVIDED IN THE FILE "LISCENSE"
 *
 * IT IS YOUR RESPONSIBILITY FOR ABSOLUTE COMPLIANCE; ANY REFUSAL WILL BE
 * HANDLED BY THE OFFICE OF COMPLIANCE
 *
 */

#pragma once

#include <assert.h>
#include <initializer_list>
#include <vector>
#include <map>
#include <typeinfo>
#include <string>

#include "SQLiteDB.h"


class Database
{
	void* _Database;

public:
	Database (const std::string File);

	void Connect ();
	void Disconnect ();

	void BeginTX ();
	void CommitTX ();
	void RollbackTX ();

protected:
	template <typename... Table>
	void InitTables (Table...Tables);
};

template <typename Elem>
class Table
{
	Database* _DB;

	void Alter (const size_t ID, const Elem Item);
	const Elem Find (const size_t ID) const;

public:
	void Insert (const Elem Item);
	void Remove (const size_t ID);

	const std::string Name;

public:
	template <typename T>
	class ElemRef
	{
		Table* _Table;
		size_t ID;

		ElemRef& operator=(const T& ref)
		{
			_Table->Alter (ID, ref);
		}

		operator const T ()
		{
			return _Table->Find (ID);
		}
	};

	ElemRef<Elem> operator[](const size_t ID)
	{
		return ElemRef<Elem> (ID);
	}
	const ElemRef<Elem> operator[](const size_t ID) const
	{
		return ElemRef<Elem> (ID);
	}
};

// TYPES

//also the null type
struct BASE
{
	static const BASE NULLVAL;
	BASE () {}
	virtual ~BASE () {};//I have to make these virtuals for typeid()
};


struct NUMERIC : BASE
{
	static const NUMERIC NULLVAL;
	NUMERIC (std::string val) : VALUE (val) {}
	NUMERIC (long long val) : VALUE (std::to_string (val)) {}
	NUMERIC (long double val) : VALUE (std::to_string (val)) {}
	NUMERIC () {}
	std::string VALUE;
	std::string& operator* ()
	{
		return VALUE;
	}
};


struct INTEGER : BASE
{
	static const INTEGER NULLVAL;
	INTEGER (long long val) : VALUE (val) {}
	INTEGER () {}
	long long VALUE;
	long long& operator* ()
	{
		return VALUE;
	}
};

struct REAL : BASE
{
	static const REAL NULLVAL;
	REAL (long double val) : VALUE (val) {}
	REAL () {}
	long double VALUE;
	long double& operator*()
	{
		return VALUE;
	}
};

struct TEXT : BASE
{
	static const TEXT NULLVAL;
	TEXT (std::string val) : VALUE (val) {}
	TEXT () {}
	std::string VALUE;
	std::string& operator* ()
	{
		return VALUE;
	}
};

enum class BYTE : unsigned char {};

struct BLOB : BASE
{
	static const BLOB NULLVAL;
	BLOB (std::vector<BYTE> val) : VALUE (val) {}
	BLOB (std::vector<unsigned char> val) : VALUE ([&] ()->std::vector<BYTE>
												   {
													   std::vector<BYTE> res;
													   for (auto& i : val)
													   {
														   res.push_back (BYTE (i));
													   }
													   return res;
												   }())
	{}
	BLOB () {}
	std::vector<BYTE> VALUE;
	std::vector<BYTE>& operator*()
	{
		return VALUE;
	}
};

//just converts it to a string
inline std::string GetType (BASE* inst)
{
	static const std::map<size_t, std::string> Types {
		{typeid(BASE).hash_code (), ""},//null type, no storage class
		{typeid(NUMERIC).hash_code (), "NUMERIC"},
		{typeid(INTEGER).hash_code (), "INTEGER"},
		{typeid(REAL).hash_code (), "REAL"},
		{typeid(TEXT).hash_code (), "TEXT"},
		{typeid(BLOB).hash_code (), "BLOB"},
	};
	return Types.at (typeid(inst).hash_code ());
}

//just converts it to a string
inline std::string GetType (const std::type_info* TI)
{
	static const std::map<size_t, std::string> Types {
		{typeid(BASE).hash_code (), ""},//null type, no storage class
		{typeid(NUMERIC).hash_code (), "NUMERIC"},
		{typeid(INTEGER).hash_code (), "INTEGER"},
		{typeid(REAL).hash_code (), "REAL"},
		{typeid(TEXT).hash_code (), "TEXT"},
		{typeid(BLOB).hash_code (), "BLOB"},
	};
	return Types.at (TI->hash_code ());
}


struct PrimaryKey final { constexpr PrimaryKey () {} };
struct ForeignKey final { const char* PT; constexpr ForeignKey (const char* pt) : PT (pt) {} };
struct Required final { constexpr Required () {} };
struct Check final { const char* Expr; constexpr Check (const char* expr) : Expr (expr) {} };
struct Unique final { const char* Col; constexpr Unique (const char* col) : Col (col) {} };


//element class
//meant to be inherited into structs
//very basic reflection capabilities
template <typename Base>//base is crtp
class Elem
{
	friend class Table<Base>;
	friend class Database;
	friend int main ();

protected:
	//maps each member to a name and typeinfo
	struct TypeMap
	{
		std::map<std::string, std::pair<size_t, const std::type_info*>> Map;

		std::string PK;
		std::vector<std::pair<std::string, std::string>> FKs;
		std::vector<std::string> UNKs;
		std::vector<std::string> REQs;

		std::string TypeName;

		//sfinae handler
		template <typename...T>
		void ProcessArgs () { static_assert(false, "INVALID ARGUMENT SPECIFICATION, IS KEY SPEC BEFORE CONDITION?"); };

		//no more args left
		void ProcessArgs () {};
		//lovely template metaprogramming function to init the map with 3+ args at a time
		template <typename T, typename S, typename I, typename...Args>
		void ProcessArgs (const T& NullVal, S Name, I Offset, Args...args);

		template <typename T, typename S, typename I, typename...Args>
		void ProcessArgs (PrimaryKey, const T& NullVal, S Name, I Offset, Args...args);

		template <typename T, typename S, typename I, typename...Args>
		void ProcessArgs (ForeignKey fk, const T& NullVal, S Name, I Offset, Args...args);

		template <typename T, typename S, typename I, typename...Args>
		void ProcessArgs (Unique, const T& NullVal, S Name, I Offset, Args...args);

		template <typename T, typename S, typename I, typename...Args>
		void ProcessArgs (Required, const T& NullVal, S Name, I Offset, Args...args);

		template <typename T, typename S, typename I, typename...Args>
		void ProcessArgs (ForeignKey fk, Unique, const T& NullVal, S Name, I Offset, Args...args);

		template <typename T, typename S, typename I, typename...Args>
		void ProcessArgs (ForeignKey fk, Required, const T& NullVal, S Name, I Offset, Args...args);

		template <typename T, typename S, typename I, typename...Args>
		void ProcessArgs (Required, Unique, const T& NullVal, S Name, I Offset, Args...args);

		template <typename T, typename S, typename I, typename...Args>
		void ProcessArgs (ForeignKey fk, Required, Unique, const T& NullVal, S Name, I Offset, Args...args);



		// params: Null type value 1, member name 1, offset 1, ...
		template <typename...Args>
		TypeMap (std::string ThisTypeName, Args...args) : TypeName (ThisTypeName)
		{//this runs only once per type, so it is fine if it takes a while
			ProcessArgs (args...);
		}

		//generates the sql query on-the-fly
		std::string GenerateTableDefinitionQuery ()
		{
			std::string Query;
			Query += "CREATE TABLE " + TypeName + " (\n";
			for (auto& i : Map)//add attribs
			{
				Query += "\t"
					+ i.first + " "
					+ ((i.second.second->name ()) != "BASE" ? (GetType(i.second.second)) : "") + " "
					+ ((PK == i.first) ? "PRIMARY KEY" : "") + " "
					+ ((std::find (REQs.cbegin (), REQs.cend (), i.first) != REQs.cend ()) ? "NOT NULL" : "") + ",\n";
			}

			for (auto& i : FKs)
			{//add fk constraints
				Query += "\t FOREIGN KEY (" + i.first + ") REFERENCES " + i.second + "(ID),\n";
			}

			for (auto& i : UNKs)
			{//add fk constraints
				Query += "\t UNIQUE (" + i + "),\n";
			}

			Query.pop_back ();//trailing comma
			Query.pop_back ();
			Query += "\n);";
			return Query;
		}

	private:
		Base GetStructFromResult (SQL::Result res)
		{
			std::vector<Base> b;
			const size_t Size = res.Data.at ("ID").size ();
			for (size_t j = 0; j < Size; j++)
			{
				for (auto& i : Map)
				{
					static const size_t BASE_CODE = typeid(BASE).hash_code (),
						NUMERIC_CODE = typeid(NUMERIC).hash_code (),
						INTEGER_CODE = typeid(INTEGER).hash_code (),
						TEXT_CODE = typeid(TEXT).hash_code (),
						BLOB_CODE = typeid(BLOB).hash_code (),
						REAL_CODE = typeid(REAL).hash_code ();
					switch (i.second.second->hash_code ())
					{
						case BASE_CODE:
							break;//null type, do nothing
						case NUMERIC_CODE:
							static_cast<NUMERIC*>(static_cast<char*>(b)[i.second.first]) = res.Data.at (i.first)[j];
					}
				}
			}

		}

		std::string GenerateSelectQuery ()
		{
			return std::string ("SELECT * FROM ") + TypeName + "  WHERE ID=?";
		}

		std::string GenerateInsertQuery ()
		{
			std::string Query = "INSERT INTO " + TypeName + " VALUES (";
			//for (auto& i : v)
			{

			}
		}
	};

private:
	const TypeMap& GetTypeMap ()
	{
		return ((Base*)this)->ThisTypeMap;
	}



private:

};





struct alignas(8) Test : Elem<Test>
{
public:
	static const Elem<Test>::TypeMap ThisTypeMap;

public:
	INTEGER A, B;
	TEXT C, D;

	Test (size_t a, size_t b, std::string c, std::string d) :
		A (a), B (b), C (c), D (d)
	{

	}
};







































//lovely template metaprogramming function to init the map with 3+ args at a time
template<typename Base>
template<typename T, typename S, typename I, typename ...Args>
inline void Elem<Base>::TypeMap::ProcessArgs (const T& NullVal, S Name, I Offset, Args ...args)//unfortunatly, recursion is unavoidable
{
	Map[Name] = std::pair<size_t, const std::type_info*> (Offset, &typeid(NullVal));  // Use direct pair construction
	ProcessArgs (args...);
}


//these filter out special attribs with good-ole tag dispatching
//yes, ORMs are really complex
template<typename Base>
template<typename T, typename S, typename I, typename ...Args>
inline void Elem<Base>::TypeMap::ProcessArgs (PrimaryKey, const T& NullVal, S Name, I Offset, Args ...args)//unfortunatly, recursion is unavoidable
{
	Map[Name] = std::pair<size_t, const std::type_info*> (Offset, &typeid(NullVal));  // Use direct pair construction
	PK = (Name);
	ProcessArgs (args...);
}

template<typename Base>
template<typename T, typename S, typename I, typename ...Args>
inline void Elem<Base>::TypeMap::ProcessArgs (ForeignKey fk, const T& NullVal, S Name, I Offset, Args ...args)//unfortunatly, recursion is unavoidable
{
	Map[Name] = std::pair<size_t, const std::type_info*> (Offset, &typeid(NullVal));  // Use direct pair construction
	FKs.push_back (std::pair<std::string, std::string> (Name, fk.PT));
	ProcessArgs (args...);
}

template<typename Base>
template<typename T, typename S, typename I, typename ...Args>
inline void Elem<Base>::TypeMap::ProcessArgs (Unique, const T& NullVal, S Name, I Offset, Args ...args)//unfortunatly, recursion is unavoidable
{
	Map[Name] = std::pair<size_t, const std::type_info*> (Offset, &typeid(NullVal));  // Use direct pair construction
	UNKs.push_back (Name);
	ProcessArgs (args...);
}

template<typename Base>
template<typename T, typename S, typename I, typename ...Args>
inline void Elem<Base>::TypeMap::ProcessArgs (Required, const T& NullVal, S Name, I Offset, Args ...args)//unfortunatly, recursion is unavoidable
{
	Map[Name] = std::pair<size_t, const std::type_info*> (Offset, &typeid(NullVal));  // Use direct pair construction
	REQs.push_back (Name);
	ProcessArgs (args...);
}

template<typename Base>
template<typename T, typename S, typename I, typename ...Args>
inline void Elem<Base>::TypeMap::ProcessArgs (ForeignKey fk, Unique, const T& NullVal, S Name, I Offset, Args ...args)//unfortunatly, recursion is unavoidable
{
	Map[Name] = std::pair<size_t, const std::type_info*> (Offset, &typeid(NullVal));  // Use direct pair construction
	FKs.push_back (std::pair<std::string, std::string> (Name, fk.PT));
	UNKs.push_back (Name);
	ProcessArgs (args...);
}

template<typename Base>
template<typename T, typename S, typename I, typename ...Args>
inline void Elem<Base>::TypeMap::ProcessArgs (ForeignKey fk, Required, const T& NullVal, S Name, I Offset, Args ...args)//unfortunatly, recursion is unavoidable
{
	Map[Name] = std::pair<size_t, const std::type_info*> (Offset, &typeid(NullVal));  // Use direct pair construction
	FKs.push_back (std::pair<std::string, std::string> (Name, fk.PT));
	REQs.push_back (Name);
	ProcessArgs (args...);
}

template<typename Base>
template<typename T, typename S, typename I, typename ...Args>
inline void Elem<Base>::TypeMap::ProcessArgs (Required, Unique, const T& NullVal, S Name, I Offset, Args ...args)//unfortunatly, recursion is unavoidable
{
	Map[Name] = std::pair<size_t, const std::type_info*> (Offset, &typeid(NullVal));  // Use direct pair construction
	UNKs.push_back (Name);
	REQs.push_back (Name);
	ProcessArgs (args...);
}

template<typename Base>
template<typename T, typename S, typename I, typename ...Args>
inline void Elem<Base>::TypeMap::ProcessArgs (ForeignKey fk, Required, Unique, const T& NullVal, S Name, I Offset, Args ...args)//unfortunatly, recursion is unavoidable
{
	Map[Name] = std::pair<size_t, const std::type_info*> (Offset, &typeid(NullVal));  // Use direct pair construction
	UNKs.push_back (Name);
	REQs.push_back (Name);
	FKs.push_back (std::pair<std::string, std::string> (Name, fk.PT));
	ProcessArgs (args...);
}

//macros to make using this feel less like steppng on a nail
#define NAMEOF(MEMBERNAME) #MEMBERNAME
#define OFFSETOF(CLASSNAME, MEMBERNAME) \
    (reinterpret_cast<size_t>(&reinterpret_cast<CLASSNAME*>(0)->MEMBERNAME))

#define FIELD(CLASSNAME, MEMBERNAME, TYPENAME) TYPENAME ::NULLVAL, NAMEOF(MEMBERNAME), OFFSETOF(CLASSNAME, MEMBERNAME)
#define PK PrimaryKey(),
#define FK(PARENT) ForeignKey{#PARENT},
#define REQ Required(),
#define UNK Unique(),