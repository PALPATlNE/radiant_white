#include "global.h"
#include "berry_tag_screen.h"
#include "berry.h"
#include "decompress.h"
#include "field_map_obj.h"
#include "item_menu.h"
#include "constants/items.h"
#include "item.h"
#include "item_use.h"
#include "main.h"
#include "menu.h"
#include "text.h"
#include "window.h"
#include "task.h"
#include "menu_helpers.h"
#include "palette.h"
#include "overworld.h"
#include "constants/songs.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "bg.h"
#include "malloc.h"
#include "scanline_effect.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "item_menu_icons.h"
#include "decompress.h"
#include "international_string_util.h"

// There are 4 windows used in berry tag screen.
enum
{
    WIN_BERRY_NAME,
    WIN_SIZE_FIRM,
    WIN_DESC,
    WIN_BERRY_TAG
};

struct BerryTagScreenStruct
{
    u16 tilemapBuffers[3][0x400];
    u16 berryId;
    u8 berrySpriteId;
    u8 flavorCircleIds[FLAVOR_COUNT];
    u16 gfxState;
};

// EWRAM vars
static EWRAM_DATA struct BerryTagScreenStruct *sBerryTag = NULL;

// const rom data
static const struct BgTemplate sBackgroundTemplates[] =
{
  {
      .bg = 0,
      .charBaseIndex = 0,
      .mapBaseIndex = 31,
      .screenSize = 0,
      .paletteMode = 0,
      .priority = 0,
      .baseTile = 0
  },
  {
      .bg = 1,
      .charBaseIndex = 0,
      .mapBaseIndex = 30,
      .screenSize = 0,
      .paletteMode = 0,
      .priority = 1,
      .baseTile = 0
  },
  {
      .bg = 2,
      .charBaseIndex = 0,
      .mapBaseIndex = 29,
      .screenSize = 0,
      .paletteMode = 0,
      .priority = 2,
      .baseTile = 0
  },
  {
      .bg = 3,
      .charBaseIndex = 0,
      .mapBaseIndex = 28,
      .screenSize = 0,
      .paletteMode = 0,
      .priority = 3,
      .baseTile = 0
  }
};

static const u16 sFontPalette[] = INCBIN_U16("graphics/interface/berry_tag_screen.gbapal");

static const u8 sTextColors[2][3] =
{
    {0, 2, 3},
    {15, 14, 13}
};

static const struct WindowTemplate sWindowTemplates[] =
{
    {0x01, 0x0b, 0x04, 0x08, 0x02, 0x0f, 0x0045}, // WIN_BERRY_NAME
    {0x01, 0x0b, 0x07, 0x12, 0x04, 0x0f, 0x0055}, // WIN_SIZE_FIRM
    {0x01, 0x04, 0x0e, 0x19, 0x04, 0x0f, 0x009d}, // WIN_DESC
    {0x00, 0x02, 0x00, 0x08, 0x02, 0x0f, 0x0101}, // WIN_BERRY_TAG
    DUMMY_WIN_TEMPLATE
};

static const u8 *const sBerryFirmnessStrings[] =
{
    gBerryFirmnessString_VerySoft,
    gBerryFirmnessString_Soft,
    gBerryFirmnessString_Hard,
    gBerryFirmnessString_VeryHard,
    gBerryFirmnessString_SuperHard
};

// this file's functions
static void CB2_InitBerryTagScreen(void);
static void HandleInitBackgrounds(void);
static void HandleInitWindows(void);
static void AddBerryTagTextToBg0(void);
static void PrintAllBerryData(void);
static void CreateBerrySprite(void);
static void CreateFlavorCircleSprites(void);
static void SetFlavorCirclesVisiblity(void);
static void PrintBerryNumberAndName(void);
static void PrintBerrySize(void);
static void PrintBerryFirmness(void);
static void PrintBerryDescription1(void);
static void PrintBerryDescription2(void);
static bool8 InitBerryTagScreen(void);
static bool8 LoadBerryTagGfx(void);
static void Task_HandleInput(u8 taskId);
static void Task_CloseBerryTagScreen(u8 taskId);
static void Task_DisplayAnotherBerry(u8 taskId);
static void TryChangeDisplayedBerry(u8 taskId, s8 toMove);
static void HandleBagCursorPositionChange(s8 toMove);

// code
void DoBerryTagScreen(void)
{
    sBerryTag = AllocZeroed(sizeof(*sBerryTag));
    sBerryTag->berryId = ItemIdToBerryType(gSpecialVar_ItemId);
    SetMainCallback2(CB2_InitBerryTagScreen);
}

static void CB2_BerryTagScreen(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    do_scheduled_bg_tilemap_copies_to_vram();
    UpdatePaletteFade();
}

static void VblankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_InitBerryTagScreen(void)
{
    while (1)
    {
        if (sub_81221EC() == TRUE)
            break;
        if (InitBerryTagScreen() == TRUE)
            break;
        if (sub_81221AC() == TRUE)
            break;
    }
}

static bool8 InitBerryTagScreen(void)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankHBlankCallbacksToNull();
        ResetVramOamAndBgCntRegs();
        clear_scheduled_bg_copies_to_vram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        gPaletteFade.bufferTransferDisabled = 1;
        gMain.state++;
        break;
    case 3:
        ResetSpriteData();
        gMain.state++;
        break;
    case 4:
        FreeAllSpritePalettes();
        gMain.state++;
        break;
    case 5:
        if (!sub_81221AC())
            ResetTasks();
        gMain.state++;
        break;
    case 6:
        HandleInitBackgrounds();
        sBerryTag->gfxState = 0;
        gMain.state++;
        break;
    case 7:
        if (LoadBerryTagGfx())
            gMain.state++;
        break;
    case 8:
        HandleInitWindows();
        gMain.state++;
        break;
    case 9:
        AddBerryTagTextToBg0();
        gMain.state++;
        break;
    case 10:
        PrintAllBerryData();
        gMain.state++;
        break;
    case 11:
        CreateBerrySprite();
        gMain.state++;
        break;
    case 12:
        CreateFlavorCircleSprites();
        SetFlavorCirclesVisiblity();
        gMain.state++;
        break;
    case 13:
        CreateTask(Task_HandleInput, 0);
        gMain.state++;
        break;
    case 14:
        BlendPalettes(-1, 0x10, 0);
        gMain.state++;
        break;
    case 15:
        BeginNormalPaletteFade(-1, 0, 0x10, 0, 0);
        gPaletteFade.bufferTransferDisabled = 0;
        gMain.state++;
        break;
    default: // done
        SetVBlankCallback(VblankCB);
        SetMainCallback2(CB2_BerryTagScreen);
        return TRUE;
    }

    return FALSE;
}

static void HandleInitBackgrounds(void)
{
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBackgroundTemplates, ARRAY_COUNT(sBackgroundTemplates));
    SetBgTilemapBuffer(2, sBerryTag->tilemapBuffers[0]);
    SetBgTilemapBuffer(3, sBerryTag->tilemapBuffers[1]);
    ResetAllBgsCoordinates();
    schedule_bg_copy_tilemap_to_vram(2);
    schedule_bg_copy_tilemap_to_vram(3);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    ShowBg(3);
}

static bool8 LoadBerryTagGfx(void)
{
    u16 i;

    switch (sBerryTag->gfxState)
    {
    case 0:
        reset_temp_tile_data_buffers();
        decompress_and_copy_tile_data_to_vram(2, gUnknown_08D9BB44, 0, 0, 0);
        sBerryTag->gfxState++;
        break;
    case 1:
        if (free_temp_tile_data_buffers_if_possible() != TRUE)
        {
            LZDecompressWram(gUnknown_08D9BF98, sBerryTag->tilemapBuffers[0]);
            sBerryTag->gfxState++;
        }
        break;
    case 2:
        LZDecompressWram(gUnknown_08D9C13C, sBerryTag->tilemapBuffers[2]);
        sBerryTag->gfxState++;
        break;
    case 3:
        if (gSaveBlock2Ptr->playerGender == MALE)
        {
            for (i = 0; i < ARRAY_COUNT(sBerryTag->tilemapBuffers[1]); i++)
                sBerryTag->tilemapBuffers[1][i] = 0x4042;
        }
        else
        {
            for (i = 0; i < ARRAY_COUNT(sBerryTag->tilemapBuffers[1]); i++)
                sBerryTag->tilemapBuffers[1][i] = 0x5042;
        }
        sBerryTag->gfxState++;
        break;
    case 4:
        LoadCompressedPalette(gUnknown_08D9BEF0, 0, 0xC0);
        sBerryTag->gfxState++;
        break;
    case 5:
        LoadCompressedObjectPic(&gUnknown_0857FDEC);
        sBerryTag->gfxState++;
        break;
    default:
        LoadCompressedObjectPalette(&gUnknown_0857FDF4);
        return TRUE; // done
    }

    return FALSE;
}

static void HandleInitWindows(void)
{
    u16 i;

    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    LoadPalette(sFontPalette, 0xF0, 0x20);
    for (i = 0; i < ARRAY_COUNT(sWindowTemplates) - 1; i++)
        PutWindowTilemap(i);
    schedule_bg_copy_tilemap_to_vram(0);
    schedule_bg_copy_tilemap_to_vram(1);
}

static void PrintTextInBerryTagScreen(u8 windowId, const u8 *text, u8 x, u8 y, s32 speed, u8 colorStructId)
{
    AddTextPrinterParameterized2(windowId, 1, x, y, 0, 0, sTextColors[colorStructId], speed, text);
}

static void AddBerryTagTextToBg0(void)
{
    memcpy(GetBgTilemapBuffer(0), sBerryTag->tilemapBuffers[2], sizeof(sBerryTag->tilemapBuffers[2]));
    FillWindowPixelBuffer(WIN_BERRY_TAG, 0xFF);
    PrintTextInBerryTagScreen(WIN_BERRY_TAG, gText_BerryTag, GetStringCenterAlignXOffset(1, gText_BerryTag, 0x40), 1, 0, 1);
    PutWindowTilemap(WIN_BERRY_TAG);
    schedule_bg_copy_tilemap_to_vram(0);
}

static void PrintAllBerryData(void)
{
    PrintBerryNumberAndName();
    PrintBerrySize();
    PrintBerryFirmness();
    PrintBerryDescription1();
    PrintBerryDescription2();
}

static void PrintBerryNumberAndName(void)
{
    const struct Berry *berry = GetBerryInfo(sBerryTag->berryId);
    ConvertIntToDecimalStringN(gStringVar1, sBerryTag->berryId, 2, 2);
    StringCopy(gStringVar2, berry->name);
    StringExpandPlaceholders(gStringVar4, gText_UnkF908Var1Var2);
    PrintTextInBerryTagScreen(WIN_BERRY_NAME, gStringVar4, 0, 1, 0, 0);
}

static void PrintBerrySize(void)
{
    const struct Berry *berry = GetBerryInfo(sBerryTag->berryId);
    PrintTextOnWindow(WIN_SIZE_FIRM, 1, gText_SizeSlash, 0, 1, TEXT_SPEED_FF, NULL);
    if (berry->size != 0)
    {
        u32 inches, fraction;

        inches = 1000 * berry->size / 254;
        if (inches % 10 > 4)
            inches += 10;
        fraction = (inches % 100) / 10;
        inches /= 100;

        ConvertIntToDecimalStringN(gStringVar1, inches, 0, 2);
        ConvertIntToDecimalStringN(gStringVar2, fraction, 0, 2);
        StringExpandPlaceholders(gStringVar4, gText_Var1DotVar2);
        PrintTextOnWindow(WIN_SIZE_FIRM, 1, gStringVar4, 0x28, 1, 0, NULL);
    }
    else
    {
        PrintTextOnWindow(WIN_SIZE_FIRM, 1, gText_ThreeMarks, 0x28, 1, 0, NULL);
    }
}

static void PrintBerryFirmness(void)
{
    const struct Berry *berry = GetBerryInfo(sBerryTag->berryId);
    PrintTextOnWindow(WIN_SIZE_FIRM, 1, gText_FirmSlash, 0, 0x11, TEXT_SPEED_FF, NULL);
    if (berry->firmness != 0)
        PrintTextOnWindow(WIN_SIZE_FIRM, 1, sBerryFirmnessStrings[berry->firmness - 1], 0x28, 0x11, 0, NULL);
    else
        PrintTextOnWindow(WIN_SIZE_FIRM, 1, gText_ThreeMarks, 0x28, 0x11, 0, NULL);
}

static void PrintBerryDescription1(void)
{
    const struct Berry *berry = GetBerryInfo(sBerryTag->berryId);
    PrintTextOnWindow(WIN_DESC, 1, berry->description1, 0, 1, 0, NULL);
}

static void PrintBerryDescription2(void)
{
    const struct Berry *berry = GetBerryInfo(sBerryTag->berryId);
    PrintTextOnWindow(WIN_DESC, 1, berry->description2, 0, 0x11, 0, NULL);
}

static void CreateBerrySprite(void)
{
    sBerryTag->berrySpriteId = CreateBerryTagSprite(sBerryTag->berryId - 1, 56, 64);
}

static void DestroyBerrySprite(void)
{
    DestroySprite(&gSprites[sBerryTag->berrySpriteId]);
    FreeBerryTagSpritePalette();
}

static void CreateFlavorCircleSprites(void)
{
    sBerryTag->flavorCircleIds[FLAVOR_SPICY] = CreateBerryFlavorCircleSprite(64);
    sBerryTag->flavorCircleIds[FLAVOR_DRY] = CreateBerryFlavorCircleSprite(104);
    sBerryTag->flavorCircleIds[FLAVOR_SWEET] = CreateBerryFlavorCircleSprite(144);
    sBerryTag->flavorCircleIds[FLAVOR_BITTER] = CreateBerryFlavorCircleSprite(184);
    sBerryTag->flavorCircleIds[FLAVOR_SOUR] = CreateBerryFlavorCircleSprite(224);
}

static void SetFlavorCirclesVisiblity(void)
{
    const struct Berry *berry = GetBerryInfo(sBerryTag->berryId);

    if (berry->spicy)
        gSprites[sBerryTag->flavorCircleIds[FLAVOR_SPICY]].invisible = 0;
    else
        gSprites[sBerryTag->flavorCircleIds[FLAVOR_SPICY]].invisible = 1;

    if (berry->dry)
        gSprites[sBerryTag->flavorCircleIds[FLAVOR_DRY]].invisible = 0;
    else
        gSprites[sBerryTag->flavorCircleIds[FLAVOR_DRY]].invisible = 1;

    if (berry->sweet)
        gSprites[sBerryTag->flavorCircleIds[FLAVOR_SWEET]].invisible = 0;
    else
        gSprites[sBerryTag->flavorCircleIds[FLAVOR_SWEET]].invisible = 1;

    if (berry->bitter)
        gSprites[sBerryTag->flavorCircleIds[FLAVOR_BITTER]].invisible = 0;
    else
        gSprites[sBerryTag->flavorCircleIds[FLAVOR_BITTER]].invisible = 1;

    if (berry->sour)
        gSprites[sBerryTag->flavorCircleIds[FLAVOR_SOUR]].invisible = 0;
    else
        gSprites[sBerryTag->flavorCircleIds[FLAVOR_SOUR]].invisible = 1;
}

static void DestroyFlavorCircleSprites(void)
{
    u16 i;

    for (i = 0; i < FLAVOR_COUNT; i++)
        DestroySprite(&gSprites[sBerryTag->flavorCircleIds[i]]);
}

static void PrepareToCloseBerryTagScreen(u8 taskId)
{
    PlaySE(SE_SELECT);
    BeginNormalPaletteFade(-1, 0, 0, 0x10, 0);
    gTasks[taskId].func = Task_CloseBerryTagScreen;
}

static void Task_CloseBerryTagScreen(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyBerrySprite();
        DestroyFlavorCircleSprites();
        Free(sBerryTag);
        FreeAllWindowBuffers();
        SetMainCallback2(bag_menu_mail_related);
        DestroyTask(taskId);
    }
}

static void Task_HandleInput(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        u16 arrowKeys = gMain.newAndRepeatedKeys & DPAD_ANY;
        if (arrowKeys == DPAD_UP)
            TryChangeDisplayedBerry(taskId, -1);
        else if (arrowKeys == DPAD_DOWN)
            TryChangeDisplayedBerry(taskId, 1);
        else if (gMain.newKeys & (A_BUTTON | B_BUTTON))
            PrepareToCloseBerryTagScreen(taskId);
    }
}

static void TryChangeDisplayedBerry(u8 taskId, s8 toMove)
{
    s16 *data = gTasks[taskId].data;
    s16 currPocketPosition = gUnknown_0203CE58.unk12[3] + gUnknown_0203CE58.unk8[3];
    u32 newPocketPosition = currPocketPosition + toMove;
    if (newPocketPosition < 46 && BagGetItemIdByPocketPosition(BAG_BERRIES, newPocketPosition) != 0)
    {
        if (toMove < 0)
            data[1] = 2;
        else
            data[1] = 1;

        data[0] = 0;
        PlaySE(SE_SELECT);
        HandleBagCursorPositionChange(toMove);
        gTasks[taskId].func = Task_DisplayAnotherBerry;
    }
}

static void HandleBagCursorPositionChange(s8 toMove)
{
    u16 *scrollPos = &gUnknown_0203CE58.unk12[3];
    u16 *cursorPos = &gUnknown_0203CE58.unk8[3];
    if (toMove > 0)
    {
        if (*cursorPos < 4 || BagGetItemIdByPocketPosition(BAG_BERRIES, *scrollPos + 8) == 0)
            *cursorPos += toMove;
        else
            *scrollPos += toMove;
    }
    else
    {
        if (*cursorPos > 3 || *scrollPos == 0)
            *cursorPos += toMove;
        else
            *scrollPos += toMove;
    }

    sBerryTag->berryId = ItemIdToBerryType(BagGetItemIdByPocketPosition(BAG_BERRIES, *scrollPos + *cursorPos));
}

static void Task_DisplayAnotherBerry(u8 taskId)
{
    u16 i;
    s16 posY;
    s16 *data = gTasks[taskId].data;
    data[0] += 0x10;
    data[0] &= 0xFF;

    if (data[1] == 1)
    {
        switch (data[0])
        {
        case 0x30:
            FillWindowPixelBuffer(0, 0);
            break;
        case 0x40:
            PrintBerryNumberAndName();
            break;
        case 0x50:
            DestroyBerrySprite();
            CreateBerrySprite();
            break;
        case 0x60:
            FillWindowPixelBuffer(1, 0);
            break;
        case 0x70:
            PrintBerrySize();
            break;
        case 0x80:
            PrintBerryFirmness();
            break;
        case 0x90:
            SetFlavorCirclesVisiblity();
            break;
        case 0xA0:
            FillWindowPixelBuffer(2, 0);
            break;
        case 0xB0:
            PrintBerryDescription1();
            break;
        case 0xC0:
            PrintBerryDescription2();
            break;
        }
    }
    else
    {
        switch (data[0])
        {
        case 0x30:
            FillWindowPixelBuffer(2, 0);
            break;
        case 0x40:
            PrintBerryDescription2();
            break;
        case 0x50:
            PrintBerryDescription1();
            break;
        case 0x60:
            SetFlavorCirclesVisiblity();
            break;
        case 0x70:
            FillWindowPixelBuffer(1, 0);
            break;
        case 0x80:
            PrintBerryFirmness();
            break;
        case 0x90:
            PrintBerrySize();
            break;
        case 0xA0:
            DestroyBerrySprite();
            CreateBerrySprite();
            break;
        case 0xB0:
            FillWindowPixelBuffer(0, 0);
            break;
        case 0xC0:
            PrintBerryNumberAndName();
            break;
        }
    }

    if (data[1] == 1)
        posY = -data[0];
    else
        posY = data[0];

    gSprites[sBerryTag->berrySpriteId].pos2.y = posY;
    for (i = 0; i < FLAVOR_COUNT; i++)
        gSprites[sBerryTag->flavorCircleIds[i]].pos2.y = posY;

    ChangeBgY(1, 0x1000, data[1]);
    ChangeBgY(2, 0x1000, data[1]);

    if (data[0] == 0)
        gTasks[taskId].func = Task_HandleInput;
}