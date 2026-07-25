/*
 * LSC Process Bar API
 * Dual Styles: V1 (Modern) & V2 (Oldschool)
 * Engine: SA-MP
 * Credits: Apies
 */
#if defined _inc_lsc_process
    #undef _inc_lsc_process
#endif
#define _inc_lsc_process

#include <a_samp>

// Auto-Streamer Support (NexQuery Textdraw Streamer)
#if defined LSC_USE_TD_STREAMER
    #include <textdraw-streamer>
#endif

// Limits
#define MAX_LSC_V1_BG 18
#define MAX_LSC_V2_BG 2

// State struct
enum E_LSC_PBAR {
    pbar_Timer,
    pbar_TimeTotal,
    pbar_TimeLeft,
    bool:pbar_Active,
    pbar_Style
}
new LscBar[MAX_PLAYERS][E_LSC_PBAR];

// Global Textdraws V1
new PlayerText:lsc_v1_bg[MAX_PLAYERS][MAX_LSC_V1_BG];
new PlayerText:lsc_v1_header[MAX_PLAYERS];
new PlayerText:lsc_v1_desc[MAX_PLAYERS];
new PlayerText:lsc_v1_decimal[MAX_PLAYERS];
new PlayerText:lsc_v1_value[MAX_PLAYERS];

// Global Textdraws V2
new PlayerText:LSCOld_bg[MAX_PLAYERS][MAX_LSC_V2_BG];
new PlayerText:LSCOld_value[MAX_PLAYERS];
new PlayerText:LSCOld_header[MAX_PLAYERS];
new PlayerText:LSCOld_desc[MAX_PLAYERS];
new PlayerText:LSCOld_decimal[MAX_PLAYERS];
new PlayerText:LSCOld_key[MAX_PLAYERS];

// Callbacks
forward LSCProgbar_Update(playerid);
forward OnLSCProgbarFinish(playerid);
forward OnLSCProgbarCancel(playerid);

// Alias
#define Process ProcessV1

stock ProcessV1(playerid, time_sec, const text[], const header[] = "Initializing_bar") 
{
    if (time_sec <= 0) time_sec = 1;
    if (LscBar[playerid][pbar_Active]) StopProcess(playerid);

    // Initializing V1 Textdraws
    for(new i=0; i<MAX_LSC_V1_BG; i++) lsc_v1_bg[playerid][i] = PlayerText:INVALID_TEXT_DRAW;

    lsc_v1_bg[playerid][0] = CreatePlayerTextDraw(playerid, 492.000, 366.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][0], 24.000, 29.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][0], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][0], 235936767);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][0], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][0], 1);
    lsc_v1_bg[playerid][1] = CreatePlayerTextDraw(playerid, 503.000, 371.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][1], 117.000, 25.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][1], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][1], 235936767);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][1], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][1], 1);
    lsc_v1_bg[playerid][2] = CreatePlayerTextDraw(playerid, 607.000, 366.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][2], 24.000, 29.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][2], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][2], 235936767);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][2], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][2], 1);
    lsc_v1_bg[playerid][3] = CreatePlayerTextDraw(playerid, 496.000, 379.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][3], 131.000, 31.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][3], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][3], 235936767);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][3], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][3], 1);
    lsc_v1_bg[playerid][4] = CreatePlayerTextDraw(playerid, 492.000, 404.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][4], 24.000, 29.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][4], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][4], 151720703);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][4], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][4], 1);
    lsc_v1_bg[playerid][5] = CreatePlayerTextDraw(playerid, 607.000, 404.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][5], 24.000, 29.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][5], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][5], 151720703);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][5], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][5], 1);
    lsc_v1_bg[playerid][6] = CreatePlayerTextDraw(playerid, 496.000, 409.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][6], 131.000, 10.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][6], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][6], 235936767);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][6], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][6], 1);
    lsc_v1_bg[playerid][7] = CreatePlayerTextDraw(playerid, 504.000, 419.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][7], 115.000, 9.449);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][7], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][7], 151720703);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][7], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][7], 1);
    lsc_v1_bg[playerid][8] = CreatePlayerTextDraw(playerid, 496.000, 410.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][8], 131.000, -1.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][8], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][8], 387657215);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][8], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][8], 1);
    lsc_v1_bg[playerid][9] = CreatePlayerTextDraw(playerid, 497.000, 372.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][9], 16.000, 18.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][9], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][9], -1416452353);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][9], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][9], 1);
    lsc_v1_bg[playerid][10] = CreatePlayerTextDraw(playerid, 498.000, 379.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][10], 16.000, 2.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][10], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][10], 235936767);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][10], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][10], 1);
    lsc_v1_bg[playerid][11] = CreatePlayerTextDraw(playerid, 498.000, 377.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][11], 16.000, 1.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][11], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][11], 235936767);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][11], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][11], 1);
    lsc_v1_bg[playerid][12] = CreatePlayerTextDraw(playerid, 600.000, 377.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][12], 7.000, 8.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][12], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][12], 1790340607);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][12], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][12], 1);
    lsc_v1_bg[playerid][13] = CreatePlayerTextDraw(playerid, 594.000, 377.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][13], 7.000, 8.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][13], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][13], -1263310337);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][13], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][13], 1);
    lsc_v1_bg[playerid][14] = CreatePlayerTextDraw(playerid, 587.000, 377.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][14], 7.000, 8.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][14], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][14], -1235265793);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][14], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][14], 1);
    lsc_v1_bg[playerid][15] = CreatePlayerTextDraw(playerid, 500.000, 402.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][15], 123.000, 4.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][15], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][15], 958407679);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][15], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][15], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][15], 1);
    lsc_v1_bg[playerid][16] = CreatePlayerTextDraw(playerid, 500.000, 411.000, "Press_H_to_cancel");
    PlayerTextDrawLetterSize(playerid, lsc_v1_bg[playerid][16], 0.129, 0.598);
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][16], 5.000, 4.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][16], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][16], 1448697855);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][16], 150);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][16], 1);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][16], 1);
    lsc_v1_bg[playerid][17] = CreatePlayerTextDraw(playerid, 498.000, 382.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, lsc_v1_bg[playerid][17], 16.000, 3.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_bg[playerid][17], 1);
    PlayerTextDrawColor(playerid, lsc_v1_bg[playerid][17], 235936767);
    PlayerTextDrawSetShadow(playerid, lsc_v1_bg[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_bg[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_bg[playerid][17], 255);
    PlayerTextDrawFont(playerid, lsc_v1_bg[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_bg[playerid][17], 1);
    lsc_v1_header[playerid] = CreatePlayerTextDraw(playerid, 514.000, 375.000, header);
    PlayerTextDrawLetterSize(playerid, lsc_v1_header[playerid], 0.218, 0.998);
    PlayerTextDrawTextSize(playerid, lsc_v1_header[playerid], 5.000, 4.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_header[playerid], 1);
    PlayerTextDrawColor(playerid, lsc_v1_header[playerid], -944323329);
    PlayerTextDrawSetShadow(playerid, lsc_v1_header[playerid], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_header[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_header[playerid], 150);
    PlayerTextDrawFont(playerid, lsc_v1_header[playerid], 1);
    PlayerTextDrawSetProportional(playerid, lsc_v1_header[playerid], 1);
    lsc_v1_decimal[playerid] = CreatePlayerTextDraw(playerid, 608.000, 376.000, "0");
    PlayerTextDrawLetterSize(playerid, lsc_v1_decimal[playerid], 0.189, 0.999);
    PlayerTextDrawTextSize(playerid, lsc_v1_decimal[playerid], 5.000, 4.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_decimal[playerid], 1);
    PlayerTextDrawColor(playerid, lsc_v1_decimal[playerid], -2139062017);
    PlayerTextDrawSetShadow(playerid, lsc_v1_decimal[playerid], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_decimal[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_decimal[playerid], 150);
    PlayerTextDrawFont(playerid, lsc_v1_decimal[playerid], 1);
    PlayerTextDrawSetProportional(playerid, lsc_v1_decimal[playerid], 1);
    lsc_v1_desc[playerid] = CreatePlayerTextDraw(playerid, 500.000, 392.000, text);
    PlayerTextDrawLetterSize(playerid, lsc_v1_desc[playerid], 0.150, 0.699);
    PlayerTextDrawTextSize(playerid, lsc_v1_desc[playerid], 5.000, 4.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_desc[playerid], 1);
    PlayerTextDrawColor(playerid, lsc_v1_desc[playerid], -1416452353);
    PlayerTextDrawSetShadow(playerid, lsc_v1_desc[playerid], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_desc[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_desc[playerid], 150);
    PlayerTextDrawFont(playerid, lsc_v1_desc[playerid], 1);
    PlayerTextDrawSetProportional(playerid, lsc_v1_desc[playerid], 1);
    lsc_v1_value[playerid] = CreatePlayerTextDraw(playerid, 500.000, 402.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, lsc_v1_value[playerid], 0.0, 4.000);
    PlayerTextDrawAlignment(playerid, lsc_v1_value[playerid], 1);
    PlayerTextDrawColor(playerid, lsc_v1_value[playerid], -1436456705);
    PlayerTextDrawSetShadow(playerid, lsc_v1_value[playerid], 0);
    PlayerTextDrawSetOutline(playerid, lsc_v1_value[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, lsc_v1_value[playerid], 255);
    PlayerTextDrawFont(playerid, lsc_v1_value[playerid], 4);
    PlayerTextDrawSetProportional(playerid, lsc_v1_value[playerid], 1);

    // Show V1
    for(new i=0; i<18; i++) PlayerTextDrawShow(playerid, lsc_v1_bg[playerid][i]);
    PlayerTextDrawShow(playerid, lsc_v1_header[playerid]);
    PlayerTextDrawShow(playerid, lsc_v1_desc[playerid]);
    PlayerTextDrawShow(playerid, lsc_v1_decimal[playerid]);
    PlayerTextDrawShow(playerid, lsc_v1_value[playerid]);

    LscBar[playerid][pbar_TimeLeft] = 0;
    LscBar[playerid][pbar_TimeTotal] = time_sec;
    LscBar[playerid][pbar_Active] = true;
    LscBar[playerid][pbar_Style] = 1;
    LscBar[playerid][pbar_Timer] = SetTimerEx("LSCProgbar_Update", 1000, true, "i", playerid);
    return 1;
}

stock ProcessV2(playerid, time_sec, const text[], const header[] = "Initializing_bar")
{
    if (time_sec <= 0) time_sec = 1;
    if (LscBar[playerid][pbar_Active]) StopProcess(playerid);

    // Initializing V2 Textdraws (Oldschool)
    LSCOld_bg[playerid][0] = CreatePlayerTextDraw(playerid, 536.000000, 111.000000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, LSCOld_bg[playerid][0], 90.000000, 39.000000);
    PlayerTextDrawAlignment(playerid, LSCOld_bg[playerid][0], 1);
    PlayerTextDrawColor(playerid, LSCOld_bg[playerid][0], 255);
    PlayerTextDrawFont(playerid, LSCOld_bg[playerid][0], 4);
    
    LSCOld_bg[playerid][1] = CreatePlayerTextDraw(playerid, 539.000000, 132.000000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, LSCOld_bg[playerid][1], 84.000000, 4.000000);
    PlayerTextDrawAlignment(playerid, LSCOld_bg[playerid][1], 1);
    PlayerTextDrawColor(playerid, LSCOld_bg[playerid][1], -1633771777);
    PlayerTextDrawFont(playerid, LSCOld_bg[playerid][1], 4);
    
    LSCOld_value[playerid] = CreatePlayerTextDraw(playerid, 539.000000, 132.000000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, LSCOld_value[playerid], 0.0, 4.000000); // Max is 84.0
    PlayerTextDrawAlignment(playerid, LSCOld_value[playerid], 1);
    PlayerTextDrawColor(playerid, LSCOld_value[playerid], -1);
    PlayerTextDrawFont(playerid, LSCOld_value[playerid], 4);
    
    LSCOld_header[playerid] = CreatePlayerTextDraw(playerid, 579.000000, 101.000000, header);
    PlayerTextDrawAlignment(playerid, LSCOld_header[playerid], 2);
    PlayerTextDrawColor(playerid, LSCOld_header[playerid], -1);
    PlayerTextDrawFont(playerid, LSCOld_header[playerid], 0);
    PlayerTextDrawSetOutline(playerid, LSCOld_header[playerid], 1);
    PlayerTextDrawSetProportional(playerid, LSCOld_header[playerid], true);
    PlayerTextDrawLetterSize(playerid, LSCOld_header[playerid], 0.449999, 1.679998);
    
    LSCOld_desc[playerid] = CreatePlayerTextDraw(playerid, 540.000000, 122.000000, text);
    PlayerTextDrawAlignment(playerid, LSCOld_desc[playerid], 1);
    PlayerTextDrawColor(playerid, LSCOld_desc[playerid], -1);
    PlayerTextDrawFont(playerid, LSCOld_desc[playerid], 1);
    PlayerTextDrawSetOutline(playerid, LSCOld_desc[playerid], 1);
    PlayerTextDrawSetProportional(playerid, LSCOld_desc[playerid], true);
    PlayerTextDrawLetterSize(playerid, LSCOld_desc[playerid], 0.149996, 0.929997);
    
    LSCOld_decimal[playerid] = CreatePlayerTextDraw(playerid, 624.000000, 122.000000, "0");
    PlayerTextDrawAlignment(playerid, LSCOld_decimal[playerid], 3);
    PlayerTextDrawColor(playerid, LSCOld_decimal[playerid], -1);
    PlayerTextDrawFont(playerid, LSCOld_decimal[playerid], 1);
    PlayerTextDrawSetOutline(playerid, LSCOld_decimal[playerid], 1);
    PlayerTextDrawSetProportional(playerid, LSCOld_decimal[playerid], true);
    PlayerTextDrawLetterSize(playerid, LSCOld_decimal[playerid], 0.149996, 0.929997);
    
    LSCOld_key[playerid] = CreatePlayerTextDraw(playerid, 615.000000, 139.000000, "Press H to Cancel Action");
    PlayerTextDrawAlignment(playerid, LSCOld_key[playerid], 3);
    PlayerTextDrawColor(playerid, LSCOld_key[playerid], -1);
    PlayerTextDrawFont(playerid, LSCOld_key[playerid], 2);
    PlayerTextDrawSetOutline(playerid, LSCOld_key[playerid], 1);
    PlayerTextDrawSetProportional(playerid, LSCOld_key[playerid], true);
    PlayerTextDrawLetterSize(playerid, LSCOld_key[playerid], 0.119997, 0.769999);
    
    // Show V2
    PlayerTextDrawShow(playerid, LSCOld_bg[playerid][0]);
    PlayerTextDrawShow(playerid, LSCOld_bg[playerid][1]);
    PlayerTextDrawShow(playerid, LSCOld_value[playerid]);
    PlayerTextDrawShow(playerid, LSCOld_header[playerid]);
    PlayerTextDrawShow(playerid, LSCOld_desc[playerid]);
    PlayerTextDrawShow(playerid, LSCOld_decimal[playerid]);
    PlayerTextDrawShow(playerid, LSCOld_key[playerid]);
    
    LscBar[playerid][pbar_TimeLeft] = 0;
    LscBar[playerid][pbar_TimeTotal] = time_sec;
    LscBar[playerid][pbar_Active] = true;
    LscBar[playerid][pbar_Style] = 2;
    LscBar[playerid][pbar_Timer] = SetTimerEx("LSCProgbar_Update", 1000, true, "i", playerid);
    
    return 1;
}

stock StopProcess(playerid)
{
    if (!LscBar[playerid][pbar_Active]) return 1;

    KillTimer(LscBar[playerid][pbar_Timer]);
    LscBar[playerid][pbar_Active] = false;

    if (LscBar[playerid][pbar_Style] == 1) {
        for (new i = 0; i < MAX_LSC_V1_BG; i++) {
            if (lsc_v1_bg[playerid][i] != PlayerText:INVALID_TEXT_DRAW) {
                PlayerTextDrawDestroy(playerid, lsc_v1_bg[playerid][i]);
                lsc_v1_bg[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            }
        }
        if (lsc_v1_header[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, lsc_v1_header[playerid]);
        if (lsc_v1_decimal[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, lsc_v1_decimal[playerid]);
        if (lsc_v1_desc[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, lsc_v1_desc[playerid]);
        if (lsc_v1_value[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, lsc_v1_value[playerid]);
    }
    else if (LscBar[playerid][pbar_Style] == 2) {
        for (new i = 0; i < MAX_LSC_V2_BG; i++) {
            if (LSCOld_bg[playerid][i] != PlayerText:INVALID_TEXT_DRAW) {
                PlayerTextDrawDestroy(playerid, LSCOld_bg[playerid][i]);
                LSCOld_bg[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            }
        }
        if (LSCOld_header[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, LSCOld_header[playerid]);
        if (LSCOld_decimal[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, LSCOld_decimal[playerid]);
        if (LSCOld_desc[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, LSCOld_desc[playerid]);
        if (LSCOld_value[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, LSCOld_value[playerid]);
        if (LSCOld_key[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, LSCOld_key[playerid]);
    }

    return 1;
}

public LSCProgbar_Update(playerid)
{
    if (!LscBar[playerid][pbar_Active]) return 0;

    LscBar[playerid][pbar_TimeLeft]++;
    new Float:progress = (float(LscBar[playerid][pbar_TimeLeft]) / float(LscBar[playerid][pbar_TimeTotal]));
    if (progress > 1.0) progress = 1.0;

    new p_val[10];
    format(p_val, sizeof(p_val), "%d", floatround(progress * 100.0));

    if (LscBar[playerid][pbar_Style] == 1) {
        // V1 width is 123.0
        PlayerTextDrawTextSize(playerid, lsc_v1_value[playerid], (123.0 * progress), 4.000);
        PlayerTextDrawShow(playerid, lsc_v1_value[playerid]);
        
        PlayerTextDrawSetString(playerid, lsc_v1_decimal[playerid], p_val);
    }
    else if (LscBar[playerid][pbar_Style] == 2) {
        // V2 width is 84.0
        PlayerTextDrawTextSize(playerid, LSCOld_value[playerid], (84.0 * progress), 4.000);
        PlayerTextDrawShow(playerid, LSCOld_value[playerid]);
        
        PlayerTextDrawSetString(playerid, LSCOld_decimal[playerid], p_val);
    }

    if (LscBar[playerid][pbar_TimeLeft] >= LscBar[playerid][pbar_TimeTotal])
    {
        StopProcess(playerid);
        CallLocalFunction("OnLSCProgbarFinish", "i", playerid);
    }
    return 1;
}

#if defined FILTERSCRIPT
    public OnFilterScriptExit()
    {
        for (new i = 0; i < MAX_PLAYERS; i++) {
            if (IsPlayerConnected(i) && LscBar[i][pbar_Active]) StopProcess(i);
        }
        #if defined LSC_OnFilterScriptExit
            return LSC_OnFilterScriptExit();
        #else
            return 1;
        #endif
    }
    #if defined _ALS_OnFilterScriptExit
        #undef OnFilterScriptExit
    #else
        #define _ALS_OnFilterScriptExit
    #endif
    #define OnFilterScriptExit LSC_OnFilterScriptExit
    #if defined LSC_OnFilterScriptExit
        forward LSC_OnFilterScriptExit();
    #endif
#else
    public OnGameModeExit()
    {
        for (new i = 0; i < MAX_PLAYERS; i++) {
            if (IsPlayerConnected(i) && LscBar[i][pbar_Active]) StopProcess(i);
        }
        #if defined LSC_OnGameModeExit
            return LSC_OnGameModeExit();
        #else
            return 1;
        #endif
    }
    #if defined _ALS_OnGameModeExit
        #undef OnGameModeExit
    #else
        #define _ALS_OnGameModeExit
    #endif
    #define OnGameModeExit LSC_OnGameModeExit
    #if defined LSC_OnGameModeExit
        forward LSC_OnGameModeExit();
    #endif
#endif

public OnPlayerDisconnect(playerid, reason)
{
    if (LscBar[playerid][pbar_Active]) StopProcess(playerid);
    #if defined LSC_OnPlayerDisconnect
        return LSC_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect LSC_OnPlayerDisconnect
#if defined LSC_OnPlayerDisconnect
    forward LSC_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (LscBar[playerid][pbar_Active])
    {
        new pState = GetPlayerState(playerid);
        new bool:pressedCancel = false;
        
        if (pState == PLAYER_STATE_ONFOOT && (newkeys & KEY_CTRL_BACK)) {
            pressedCancel = true;
        }
        else if ((pState == PLAYER_STATE_DRIVER || pState == PLAYER_STATE_PASSENGER) && (newkeys & KEY_CROUCH)) {
            pressedCancel = true;
        }
        
        if (pressedCancel)
        {
            StopProcess(playerid);
            CallLocalFunction("OnLSCProgbarCancel", "i", playerid);
        }
    }
    #if defined LSC_OnPlayerKeyStateChange
        return LSC_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange LSC_OnPlayerKeyStateChange
#if defined LSC_OnPlayerKeyStateChange
    forward LSC_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif
