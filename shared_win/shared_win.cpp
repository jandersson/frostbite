#include "shared_win.h"

#ifdef WIN32
/* windows specific - mingw32 */
// http://gcc.gnu.org/onlinedocs/gcc/Variable-Attributes.html - shared
#define SHARED __attribute__((section(".shr"), shared))

char exp[SharedWin::expRows][SharedWin::expY][SharedWin::expZ] SHARED = {{"", "", ""}};

bool standing SHARED = false;
bool sitting SHARED = false;
bool kneeling SHARED = false;
bool prone SHARED = false;
bool stunned SHARED = false;
bool bleeding SHARED = false;
bool hidden SHARED = false;
bool invisible SHARED = false;
bool webbed SHARED = false;
bool joined SHARED = false;
bool dead SHARED = false;

char inventory[SharedWin::inventorySize] SHARED = "";

char container[SharedWin::containerSize] SHARED = "";

char wieldRight[SharedWin::wieldSize] SHARED = "";
char wieldRightNoun[SharedWin::wieldSize] SHARED = "";
char wieldLeft[SharedWin::wieldSize] SHARED = "";
char wieldLeftNoun[SharedWin::wieldSize] SHARED = "";

int health SHARED = 0;
int concentration SHARED = 0;
int spirit SHARED = 0;
int fatigue SHARED = 0;

char roomTitle[SharedWin::roomTitleSize] SHARED = "";
char roomDescription[SharedWin::roomDescriptionSize] SHARED = "";
char roomObjects[SharedWin::roomObjectsSize] SHARED = "";
char roomPlayers[SharedWin::roomPlayersSize] SHARED = "";
char roomExits[SharedWin::roomExitsSize] SHARED = "";

int rt SHARED = 0;
#else
/* not shared in other platforms */
char exp[SharedWin::expRows][SharedWin::expY][SharedWin::expZ] = {{"", "", ""}};

bool standing = false;
bool sitting = false;
bool kneeling = false;
bool prone = false;
bool stunned = false;
bool bleeding = false;
bool hidden = false;
bool invisible = false;
bool webbed = false;
bool joined = false;
bool dead = false;

char inventory[SharedWin::inventorySize] = "";

char container[SharedWin::containerSize] = "";

char wieldRight[SharedWin::wieldSize] = "";
char wieldRightNoun[SharedWin::wieldSize] = "";
char wieldLeft[SharedWin::wieldSize] = "";
char wieldLeftNoun[SharedWin::wieldSize] = "";

int health = 0;
int concentration = 0;
int spirit = 0;
int fatigue = 0;

char roomTitle[SharedWin::roomTitleSize] = "";
char roomDescription[SharedWin::roomDescriptionSize] = "";
char roomObjects[SharedWin::roomObjectsSize] = "";
char roomPlayers[SharedWin::roomPlayersSize] = "";
char roomExits[SharedWin::roomExitsSize] = "";

int rt = 0;

#endif


/* exp */

extern "C" EXPORT_FUNCTION int getExpIndex(const char name[]) {
    size_t expSize = sizeof(exp) / sizeof(exp[0]);
    size_t nameSize = strlen(name);

    for(unsigned int i = 0; i < expSize; i++) {
        for(unsigned int j = 0; j < nameSize; j++) {
            if(exp[i][0][j] == 0 || exp[i][0][j] != name[j]) {
                break;
            } else {
                if(j == nameSize - 1) {
                    return i;
                }
            }
        }
    }
    return -1;
}

int getLastFreeIndex() {
    size_t expSize = sizeof(exp) / sizeof(exp[0]);

    for(unsigned int i = 0; i < expSize; i++) {
        if(exp[i][0][0] == 0) {
            return i;
        }
    }
    return -1;
}

void setExp(int index, const char name[], const char rank[], const char state[]) {
    strcpy(exp[index][0], name);
    strcpy(exp[index][1], rank);
    strcpy(exp[index][2], state);
}

void removeExp(int index) {
    //strcpy(exp[index][0], ""); -- produces duplicate values
    strcpy(exp[index][1], "");
    strcpy(exp[index][2], "");
}

extern "C" EXPORT_FUNCTION void setExpField(const char name[], const char rank[], const char state[]) {
    int index = getExpIndex(name);

    if(index == -1) {
        int free = getLastFreeIndex();
        if(free != -1) {
            setExp(free, name, rank, state);
        }
    } else {
        setExp(index, name, rank, state);
    }
}

extern "C" EXPORT_FUNCTION void removeExpField(const char name[]) {
    int index = getExpIndex(name);

    if(index != -1) {
        removeExp(index);
    }
}

extern "C" EXPORT_FUNCTION int getExpRank(const char name[]) {
    int index = getExpIndex(name);

    if(index >= 0 && index < SharedWin::expRows) {
        return atoi(exp[index][1]);
    }
    return 0;
}

extern "C" EXPORT_FUNCTION int getExpState(const char name[]) {
    int index = getExpIndex(name);

    if(index >= 0 && index < SharedWin::expRows) {
        return atoi(exp[index][2]);
    }
    return 0;
}

/* status getters/setters */

extern "C" EXPORT_FUNCTION bool getStanding() {
    return standing;
}

extern "C" EXPORT_FUNCTION void setStanding(bool _standing) {
    standing = _standing;
}

extern "C" EXPORT_FUNCTION bool getSitting() {
    return sitting;
}

extern "C" EXPORT_FUNCTION void setSitting(bool _sitting) {
    sitting = _sitting;
}

extern "C" EXPORT_FUNCTION bool getKneeling() {
    return kneeling;
}

extern "C" EXPORT_FUNCTION void setKneeling(bool _kneeling) {
    kneeling = _kneeling;
}

extern "C" EXPORT_FUNCTION bool getProne() {
    return prone;
}

extern "C" EXPORT_FUNCTION void setProne(bool _prone) {
    prone = _prone;
}

extern "C" EXPORT_FUNCTION bool getStunned() {
    return stunned;
}

extern "C" EXPORT_FUNCTION void setStunned(bool _stunned) {
    stunned = _stunned;
}

extern "C" EXPORT_FUNCTION bool getBleeding() {
    return bleeding;
}

extern "C" EXPORT_FUNCTION void setBleeding(bool _bleeding) {
    bleeding = _bleeding;
}

extern "C" EXPORT_FUNCTION bool getHidden() {
    return hidden;
}

extern "C" EXPORT_FUNCTION void setHidden(bool _hidden) {
    hidden = _hidden;
}

extern "C" EXPORT_FUNCTION bool getInvisible() {
    return invisible;
}

extern "C" EXPORT_FUNCTION void setInvisible(bool _invisible) {
    invisible = _invisible;
}

extern "C" EXPORT_FUNCTION bool getWebbed() {
    return webbed;
}

extern "C" EXPORT_FUNCTION void setWebbed(bool _webbed) {
    webbed = _webbed;
}

extern "C" EXPORT_FUNCTION bool getJoined() {
    return joined;
}

extern "C" EXPORT_FUNCTION void setJoined(bool _joined) {
    joined = _joined;
}

extern "C" EXPORT_FUNCTION bool getDead() {
    return dead;
}

extern "C" EXPORT_FUNCTION void setDead(bool _dead) {
    dead = _dead;
}

/* inventory */

extern "C" EXPORT_FUNCTION char* getInventory() {
    return inventory;
}

extern "C" EXPORT_FUNCTION void setInventory(const char inv[]) {
    strcpy(inventory, inv);
}

/* container */

extern "C" EXPORT_FUNCTION char* getContainer() {
    return container;
}

extern "C" EXPORT_FUNCTION void setContainer(const char cont[]) {
    strcpy(container, cont);
}

/* wield */

extern "C" EXPORT_FUNCTION char* getWieldRight() {
    return wieldRight;
}

extern "C" EXPORT_FUNCTION void setWieldRight(const char wield[]) {
    strcpy(wieldRight, wield);
}

extern "C" EXPORT_FUNCTION char* getWieldRightNoun() {
    return wieldRightNoun;
}

extern "C" EXPORT_FUNCTION void setWieldRightNoun(const char wield[]) {
    strcpy(wieldRightNoun, wield);
}

extern "C" EXPORT_FUNCTION char* getWieldLeft() {
    return wieldLeft;
}

extern "C" EXPORT_FUNCTION void setWieldLeft(const char wield[]) {
    strcpy(wieldLeft, wield);
}

extern "C" EXPORT_FUNCTION char* getWieldLeftNoun() {
    return wieldLeftNoun;
}

extern "C" EXPORT_FUNCTION void setWieldLeftNoun(const char wield[]) {
    strcpy(wieldLeftNoun, wield);
}

/* vitals */

extern "C" EXPORT_FUNCTION int getHealth() {
    return health;
}

extern "C" EXPORT_FUNCTION void setHealth(int _health) {
    health = _health;
}

extern "C" EXPORT_FUNCTION int getConcentration() {
    return concentration;
}

extern "C" EXPORT_FUNCTION void setConcentration(int _concentration) {
    concentration = _concentration;
}

extern "C" EXPORT_FUNCTION int getSpirit() {
    return spirit;
}

extern "C" EXPORT_FUNCTION void setSpirit(int _spirit) {
    spirit = _spirit;
}

extern "C" EXPORT_FUNCTION int getFatigue() {
    return fatigue;
}

extern "C" EXPORT_FUNCTION void setFatigue(int _fatigue) {
    fatigue = _fatigue;
}

/* room */

extern "C" EXPORT_FUNCTION char* getRoomTitle() {
    return roomTitle;
}

extern "C" EXPORT_FUNCTION void setRoomTitle(const char title[]) {
    strcpy(roomTitle, title);
}

extern "C" EXPORT_FUNCTION char* getRoomDescription() {
    return roomDescription;
}

extern "C" EXPORT_FUNCTION void setRoomDescription(const char desc[]) {
    strcpy(roomDescription, desc);
}

extern "C" EXPORT_FUNCTION char* getRoomObjects() {
    return roomObjects;
}

extern "C" EXPORT_FUNCTION void setRoomObjects(const char obj[]) {
    strcpy(roomObjects, obj);
}

extern "C" EXPORT_FUNCTION char* getRoomPlayers() {
    return roomPlayers;
}

extern "C" EXPORT_FUNCTION void setRoomPlayers(const char players[]) {
    strcpy(roomPlayers, players);
}

extern "C" EXPORT_FUNCTION char* getRoomExits() {
    return roomExits;
}

extern "C" EXPORT_FUNCTION void setRoomExits(const char exits[]) {
    strcpy(roomExits, exits);
}

extern "C" EXPORT_FUNCTION int getRt() {
    return rt;
}

extern "C" EXPORT_FUNCTION void setRt(int _rt) {
    rt = _rt;
}
