#include <mod/amlmod.h>
#include "iimgui.h"

MYMOD(net.rusjj.gtasa.debuginfo, SA Debug Info, 1.0, RusJJ)

uintptr_t pGTASA = 0;
void* hGTASA = NULL;
IImGui* imgui = NULL;

float *fps;
int *ms_memoryUsed, *ms_memoryAvailable;

struct Vec3 { float x,y,z; };
void (*FindPlayerCoors)(Vec3&, int);
uintptr_t (*FindPlayerPed)(int);

Vec3 vecPos;
inline const char* GetPedStateEnum(int e)
{
    switch(e)
    {
        default: return "UNKNOWN";
        case 0:  return "NONE";
        case 1:  return "IDLE";
        case 2:  return "LOOK_ENTITY";
        case 3:  return "LOOK_HEADING";
        case 4:  return "WANDER_RANGE";
        case 5:  return "WANDER_PATH";
        case 6:  return "SEEK_POSITION";
        case 7:  return "SEEK_ENTITY";
        case 8:  return "FLEE_POSITION";
        case 9:  return "FLEE_ENTITY";
        case 10: return "PURSUE";
        case 11: return "FOLLOW_PATH";
        case 12: return "SNIPER_MODE";
        case 13: return "ROCKETLAUNCHER_MODE";
        case 14: return "DUMMY";
        case 15: return "PAUSE";
        case 16: return "ATTACK";
        case 17: return "FIGHT";
        case 18: return "FACE_PHONE";
        case 19: return "MAKE_PHONECALL";
        case 20: return "CHAT";
        case 21: return "MUG";
        case 22: return "AIMGUN";
        case 23: return "AI_CONTROL";
        case 24: return "SEEK_CAR";
        case 25: return "SEEK_BOAT_POSITION";
        case 26: return "FOLLOW_ROUTE";
        case 27: return "CPR";
        case 28: return "SOLICIT";
        case 29: return "BUY_ICE_CREAM";
        case 30: return "INVESTIGATE_EVENT";
        case 31: return "EVADE_STEP";
        case 32: return "ON_FIRE";
        case 33: return "SUNBATHE";
        case 34: return "FLASH";
        case 35: return "JOG";
        case 36: return "ANSWER_MOBILE";
        case 37: return "HANG_OUT";
        case 38: return "STATES_NO_AI";
        case 39: return "ABSEIL_FROM_HELI";
        case 40: return "SIT";
        case 41: return "JUMP";
        case 42: return "FALL";
        case 43: return "GETUP";
        case 44: return "STAGGER";
        case 45: return "EVADE_DIVE";
        case 46: return "STATES_CAN_SHOOT";
        case 47: return "ENTER_TRAIN";
        case 48: return "EXIT_TRAIN";
        case 49: return "ARREST_PLAYER";
        case 50: return "DRIVING";
        case 51: return "PASSENGER";
        case 52: return "TAXI_PASSENGER";
        case 53: return "OPEN_DOOR";
        case 54: return "DIE";
        case 55: return "DEAD";
        case 56: return "DIE_BY_STEALTH";
        case 57: return "CARJACK";
        case 58: return "DRAGGED_FROM_CAR";
        case 59: return "ENTER_CAR";
        case 60: return "STEAL_CAR";
        case 61: return "EXIT_CAR";
        case 62: return "HANDS_UP";
        case 63: return "ARRESTED";
        case 64: return "DEPLOY_STINGER";
    }
}
void OnImGuiRender()
{
    if(imgui->Begin("DebugInfo_SA", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings))
    {
        imgui->SetWindowPos({0,0});

        FindPlayerCoors(vecPos, -1);
        uintptr_t pedPtr = FindPlayerPed(-1);
        int pedState = *(int*)(pedPtr + 0x44C);
        imgui->Text("| FPS %.1f | X %.3f | Y %.3f | Z %.3f | HP %.2f/%.2f | Skin %d | \n| Interior %d | Mem %.2f/%.2f MB | Speed %.2f | State %s |",
            *fps, vecPos.x, vecPos.y, vecPos.z, *(float*)(pedPtr + 0x544), *(float*)(pedPtr + 0x548), *(uint16_t*)(pedPtr + 0x26),
            *(uint8_t*)(pedPtr + 0x33), ((float)(*ms_memoryUsed) / 1048576.0f), ((float)(*ms_memoryAvailable) / 1048576.0f), *(float*)(pedPtr + 0xD8), GetPedStateEnum(pedState));
    }
    imgui->End();
}

extern "C" void OnModLoad()
{
    pGTASA = aml->GetLib("libGTASA.so");
    hGTASA = aml->GetLibHandle("libGTASA.so");

    imgui = (IImGui*)GetInterface("ImGui");
    imgui->AddRenderListener((void*)OnImGuiRender);

    SET_TO(fps, aml->GetSym(pGTASA, "_ZN6CTimer8game_FPSE"));
    SET_TO(FindPlayerCoors, aml->GetSym(pGTASA, "_Z15FindPlayerCoorsi"));
    SET_TO(FindPlayerPed, aml->GetSym(pGTASA, "_Z13FindPlayerPedi"));
    SET_TO(ms_memoryUsed, aml->GetSym(pGTASA, "_ZN10CStreaming13ms_memoryUsedE"));
    SET_TO(ms_memoryAvailable, aml->GetSym(pGTASA, "_ZN10CStreaming18ms_memoryAvailableE"));
}