const name ACTIVE = "active"_n;
//Actions
const name NEWTAG = "newtag"_n;
const name RMVTAG = "rmvtag"_n;
//NFT group names
const name AVATARS = "avatars"_n;
const name BADGES = "badges"_n;
const name FLAGS = "flags"_n;
const name ARTS = "arts"_n;

const name TOOLS = "tools"_n;

const name MINERS = "miners"_n;
const name MINESITES = "minesites"_n;
const name REFINERY = "refineries"_n;

//attributes
const name MINTDATE = "mintdate"_n;
const name STARS = "stars"_n;
const name POINTS = "points"_n;
const name PROGRESS = "progress"_n;
const name TRADES = "trades"_n;
const name TOTALPRICE = "totalprice"_n;
const name NOTCONSUME = "notconsume"_n;
const name ENHPOINTS = "enhpoints"_n;
const name SET = "set"_n;

//tags
const name DATA = "data"_n;
const name TITLE = "title"_n;
const name ASSET = "asset"_n;
const name CREATOR = "creator"_n;
const name FORSELL = "forsell"_n;
const name DESCRIPTION = "description"_n;
bool isScoreGroup(name group){
  return group == AVATARS ||  group == BADGES ||  group == FLAGS ||  group == ARTS;
}

bool isConsumable(name group){
  return group == TOOLS;
}

name _code = ""_n;