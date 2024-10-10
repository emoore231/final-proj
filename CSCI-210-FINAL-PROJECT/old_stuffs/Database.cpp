#include "Database.h"
const BASE BASE::NULLVAL {};
const NUMERIC NUMERIC::NULLVAL {};
const INTEGER INTEGER::NULLVAL {};
const REAL REAL::NULLVAL {};
const TEXT TEXT::NULLVAL {};
const BLOB BLOB::NULLVAL {};

const Elem<Test>::TypeMap Test::ThisTypeMap { "TEST",
											  PK FIELD (Test, A, INTEGER),
											  FK(TEST2) REQ FIELD (Test, B, INTEGER),
											  REQ FIELD (Test, C, TEXT),
											  REQ FIELD (Test, D, TEXT)
};

