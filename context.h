#pragma once

class Data;
struct Intend;
struct StateTable;

struct GameCtx {
	Data& data;
	Intend& intend;
	StateTable& flag;
};
