
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// When set to true, creation and deletion of objects will be shown
const bool SHOW_MESSAGES = false;

const int ARGC_MAX = 20;

// actiavte action constants

const int NOTHING = 0;

const int BLOCK_SET = 1;
const int HIDE_SET = 2;

const int BLOCK_TOGGLE = 3;
const int HIDE_TOGGLE = 4;

const int ROTATE = 5;
const int ROTATE_SET = 6;

const int POSITION = 7;
const int FACE = 8;

const int ROOM_SET = 9;

const int OBTAINABLE_SET = 10;
const int OBTAIN_SET = 11;

const int OBTAINABLE_TOGGLE = 12;
const int OBTAIN_TOGGLE = 13;

// compass directions
// -!- DIRECTIONS NEED TO BE CONTIGUOUS -!-
// -!- NO-DIRECTION MUST ALWAYS BE SMALLEST -!-
//
const int NO_DIRECTION = -3;

const int OPPOSITE = -2;
const int CENTER = -1;

const int N = 0;
const int NNE = 1;
const int NE = 2;
const int ENE = 3;
const int E = 4;
const int ESE = 5;
const int SE = 6;
const int SSE = 7;
const int S = 8;
const int SSW = 9;
const int SW = 10;
const int WSW = 11;
const int W = 12;
const int WNW = 13;
const int NW = 14;
const int NNW = 15;

const int DIRECTION_MAX = 16;

// room types
const std::string ROOM = "ROOM";
const std::string DIAGONAL_ROOM = "DIAGONAL_ROOM";
const std::string CORRIDOR_ROOM = "CORRIDOR_ROOM";
const std::string ROUND_ROOM = "ROUND_ROOM";
const std::string ROTATING_ROOM = "ROTATING_ROOM";

// item types
const std::string ITEM = "ITEM";

// character types
const std::string CHARACTER = "CHARACTER";

// arrays that are used for quick access to strings
// -!- NEED TO HAVE INDICES CORRESPONDING TO (DIRECTION - NO_DIRECTION) -!-
const std::string DIRECTION_ARRAY_LONG[] = {
  "NO_DIRECTION"
    , "OPPOSITE"
    , "Center"
    , "North"
    , "North-by-Northeast"
    , "Northeast"
    , "East-by-Northeast"
    , "East"
    , "East-by-Southeast"
    , "Southeast"
    , "South-by-Southeast"
    , "South"
    , "South-by-Southwest"
    , "Southwest"
    , "West-by-Southwest"
    , "West"
    , "West-by-Northwest"
    , "Northwest"
    , "North-by-Northwest"
};

const std::string DIRECTION_ARRAY_SHORT[] = {
  "N/D"
    , "OPP"
    , "C"
    , "N"
    , "NNE"
    , "NE"
    , "ENE"
    , "E"
    , "ESE"
    , "SE"
    , "SSE"
    , "S"
    , "SSW"
    , "SW"
    , "WSW"
    , "W"
    , "WNW"
    , "NW"
    , "NNW"
};

#endif
