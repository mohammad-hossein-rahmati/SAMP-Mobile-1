#include "main.h"
#include "CServerManager.h"
#include "settings.h"

#include "gui/gui.h"
extern UI *pUI;
#include "net/netgame.h"
extern CNetGame *pNetGame;
#include "java/jniutil.h"

extern CJavaWrapper *pJavaWrapper;
#define SRV_NAME1 "LIFEGAME ROLEPLAY"
#define SRV_NAME2 "LIFEGAME CNR"
const char* g_szServerNames[] = {
        (SRV_NAME1),
        (SRV_NAME2)
};
constexpr size_t MAX_SERVERS = sizeof(g_szServerNames)
        / sizeof(g_szServerNames[0]);

#define IP1 "life-game.ir" // len 9
#define IP2 "life-game.ir" // len 9
const CServerInstance::CServerInstanceEncrypted g_sEncryptedAddresses[MAX_SERVERS] = {
        CServerInstance::create((IP1), 1, 9, 7777, false),
        CServerInstance::create((IP2), 1, 9, 7777, false)
};

int CServerInstance::iServer = -1;
void CServerInstance::initConnection(int id) {
    CServerInstance::iServer = id;

    std::string srvStr = "{\"value\":" + std::to_string(CServerInstance::iServer) + "}";

    if(CServerInstance::iServer == -1) {
        pNetGame = new CNetGame(
                ("life-game.ir"),
                7777,
                pSettings->Get().szNickName,
                pSettings->Get().szPassword);
    } else {
        pNetGame = new CNetGame(
                g_sEncryptedAddresses[CServerInstance::iServer].decrypt(),
                g_sEncryptedAddresses[CServerInstance::iServer].getPort(),
                pSettings->Get().szNickName,
                pSettings->Get().szPassword);
    }
}
