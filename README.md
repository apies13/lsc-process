# LSC Process Bar

[![Pawn](https://img.shields.io/badge/Language-Pawn-blue.svg)](#)
[![Release](https://img.shields.io/badge/release-v2.0.0-blue.svg)](#)
[![Downloads](https://img.shields.io/badge/downloads-0-brightgreen.svg)](#)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](#)
[![Platform](https://img.shields.io/badge/Platform-SA--MP%20%7C%20open.mp-lightgrey.svg)](#)
[![sampctl](https://img.shields.io/badge/sampctl-LSC--Process-2f2f2f.svg)](#)

### UI Previews

<div align="center">
  <img src="https://i.ibb.co.com/LDMV2mD2/Screenshot-2026-07-25-084522.png" alt="Modern Style (V1)" width="45%" />
  <img src="https://i.ibb.co.com/201CB28L/Screenshot-2026-07-25-083301.png" alt="Oldschool Style (V2)" width="45%" />
  <br> 
  <i>Left: Modern Layout (V1) | Right: Classic Box Layout (V2)</i>
</div>

---

### sampctl Installation

This module provides full support for `sampctl` package management. Install it directly into your environment securely:

```bash
sampctl package install apies13/lsc-process
```
**Important:** `sampctl` will automatically download both versions to your dependencies folder. To choose your engine, just dictate it in your script's inclusion:
- Use `#include <lsc_process>` if you build for **SA-MP**.
- Use `#include <lsc_process_omp>` if you build for **open.mp**.

---

[English Documentation](#english) | [Dokumentasi Indonesia](#indonesia)

---

<br>

<a id="english"></a>
## English Documentation

LSC Process Bar is a dynamic, lightweight, and elegant textdraw-based loading and progress bar API designed specifically for SA-MP and open.mp. With complete backward compatibility, dual design architecture, and native Textdraw Streamer support, it serves as an optimal plug-and-play solution for roleplay servers and interactive SA-MP environments.

### Core Features
- **Dual Engine Architecture**: Fully supports both **SA-MP** (`lsc_process.inc`) and **open.mp** (`lsc_process_omp.inc`).
- **Two Distinct UI Styles**: Select between a sleek Modern layout (V1) or a classic Box design (V2).
- **Dynamic Progression Mapping**: Accurate progress calculation mapped natively to textdraw scaling algorithms.
- **Robust Cancellation Event**: Intelligent abort mechanics utilizing state-aware checks (`KEY_CTRL_BACK` on-foot, `KEY_CROUCH` in-vehicle) to prevent overlapping inputs.
- **Streamer Interoperability**: Seamlessly integrates with NexQuery's Textdraw Streamer via a preprocessor macro.
- **Modular Callbacks**: Operates securely utilizing `CallLocalFunction`, eliminating the necessity for complex state forwarding within your primary gamemode.

### Manual Standalone Installation
1. Download the `inc` matching your server engine type.
2. Store the file into your compiler's internal `include` directory (i.e., `pawno/include` or `qawno/include`).
3. Import the API globally into your gamemode script:

```pawn
// If using the external Textdraw Streamer plugin:
#define LSC_USE_TD_STREAMER
#include <lsc_process> // Alter to <lsc_process_omp> if operating on open.mp

// If operating purely on native server core limits (No Streamer required):
#include <lsc_process> // Alter to <lsc_process_omp> if operating on open.mp
```

### Usage Reference

```pawn
CMD:testprog1(playerid, params[])
{
    if (GetPVarInt(playerid, "pTestProg1") == 1)
        return SendClientMessage(playerid, 0xFF0000FF, "ERROR: {FFFFFF}Kamu sedang mengetes progress bar V1!");
        
    SetPVarInt(playerid, "pTestProg1", 1);
    ApplyAnimation(playerid, "CHAINSAW", "WEAPON_csaw", 4.1, 1, 0, 0, 1, 0, 1);
    
     // UI: ProcessV1 or ProcessV2 (playerid, duration_seconds, "Module Description", "Module Header");
    ProcessV1(playerid, 10, "Menambang_Batu..", "Test_Miner_V1");
    return 1;
}

CMD:testprog2(playerid, params[])
{
    if (GetPVarInt(playerid, "pTestProg2") == 1)
        return SendClientMessage(playerid, 0xFF0000FF, "ERROR: {FFFFFF}Kamu sedang mengetes progress bar V2!");
        
    SetPVarInt(playerid, "pTestProg2", 1);
    ApplyAnimation(playerid, "CHAINSAW", "WEAPON_csaw", 4.1, 1, 0, 0, 1, 0, 1);
    
     // UI: ProcessV1 or ProcessV2 (playerid, duration_seconds, "Module Description", "Module Header");
    ProcessV2(playerid, 10, "Menambang_Batu..", "Test_Miner_V2");
    return 1;
}

// Callbacks

public OnLSCProgbarFinish(playerid)
{
    if (GetPVarInt(playerid, "pTestProg1") == 1)
    {
        ClearAnimations(playerid);
        SendClientMessage(playerid, 0x00FF00FF, "SYSTEM: {FFFFFF}Progress bar V1 selesai! 1x Batu didapatkan!");
        DeletePVar(playerid, "pTestProg1");
    }
    else if (GetPVarInt(playerid, "pTestProg2") == 1)
    {
        ClearAnimations(playerid);
        SendClientMessage(playerid, 0x00FF00FF, "SYSTEM: {FFFFFF}Progress bar V2 selesai! 1x Besi didapatkan!");
        DeletePVar(playerid, "pTestProg2");
    }
    return 1;
}

public OnLSCProgbarCancel(playerid)
{
    if (GetPVarInt(playerid, "pTestProg1") == 1)
    {
        ClearAnimations(playerid);
        SendClientMessage(playerid, 0xFF0000FF, "SYSTEM: {FFFFFF}Progress bar V1 dibatalkan!");
        DeletePVar(playerid, "pTestProg1");
    }
    else if (GetPVarInt(playerid, "pTestProg2") == 1)
    {
        ClearAnimations(playerid);
        SendClientMessage(playerid, 0xFF0000FF, "SYSTEM: {FFFFFF}Progress bar V2 dibatalkan!");
        DeletePVar(playerid, "pTestProg2");
    }
    return 1;
}
```

---

<br>

<a id="indonesia"></a>
## Dokumentasi Indonesia

LSC Process Bar adalah sistem loading dan progress bar berbasis textdraw yang sangat dinamis, ringan, dan dirancang khusus untuk ekosistem SA-MP maupun open.mp. Menawarkan kompatibilitas skala penuh, opsi desain kustom, dan dukungan natif untuk Textdraw Streamer.

### Fitur Fundamental
- **Arsitektur Mesin Ganda**: Berjalan secara stabil baik di **SA-MP** (`lsc_process.inc`) maupun **open.mp** (`lsc_process_omp.inc`).
- **Antarmuka Ganda (Dual UI)**: Mendukung desain Modern layar penuh (V1) dan desain Klasik minimalis (V2).
- **Kalkulasi Progres Dinamis**: Skala bar diperbarui (memanjang/memendek) secara mulus berdasarkan parameter durasi detik.
- **Pembatalan Logika Cerdas**: Mendukung pembatalan berbasis `PlayerState` (`KEY_CTRL_BACK` di jalan, dan tombol *Horn* di dalam kendaraan) demi menghindari celah *input overlap*.
- **Interoperabilitas Streamer**: Mampu dialihkan langsung ke memori pemrosesan NexQuery Textdraw Streamer lewat preprocessor.
- **Modular Internal Callback**: Mengeksekusi blok event tanpa menyaring "forward" eksternal berkat fungsi `CallLocalFunction`.

### Panduan Instalasi (Via sampctl / Otomatis)
Jika project kamu sudah menggunakan `sampctl`, sangat disarankan untuk menginstallnya secara otomatis:
```bash
sampctl package install apies13/lsc-process
```
*Catatan: `sampctl` akan mengunduh versi SA-MP dan open.mp secara bersamaan. Untuk memfilternya, kamu cukup menentukannya di file `.pwn` kamu: ingin `#include <lsc_process>` (SA-MP) atau `#include <lsc_process_omp>` (open.mp).*

---

### Panduan Instalasi (Manual)
1. Ekstrak dan pindahkan spesifik modul `.inc` ke dalam folder *include* engine kompilator (`pawno/include` untuk sa-mp atau `qawno/include` untuk open.mp).
2. Deklarasikan integrasi library ini di dokumen sentral *.pwn*:

```pawn
// Jika implementasi melibatkan penggunaan plugin textdraw-streamer eksternal:
#define LSC_USE_TD_STREAMER
#include <lsc_process> // Sesuaikan dengan <lsc_process_omp> pada sistem open.mp

// Jika implementasi hanya mengandalkan limit slot native murni:
#include <lsc_process> // Sesuaikan dengan <lsc_process_omp> pada sistem open.mp
```

### Referensi Dasar Penggunaan

```pawn
CMD:testprog1(playerid, params[])
{
    if (GetPVarInt(playerid, "pTestProg1") == 1)
        return SendClientMessage(playerid, 0xFF0000FF, "ERROR: {FFFFFF}Kamu sedang mengetes progress bar V1!");
        
    SetPVarInt(playerid, "pTestProg1", 1);
    ApplyAnimation(playerid, "CHAINSAW", "WEAPON_csaw", 4.1, 1, 0, 0, 1, 0, 1);
    
     // UI: ProcessV1 or ProcessV2 (playerid, duration_seconds, "Module Description", "Module Header");
    ProcessV1(playerid, 10, "Menambang_Batu..", "Test_Miner_V1");
    return 1;
}

CMD:testprog2(playerid, params[])
{
    if (GetPVarInt(playerid, "pTestProg2") == 1)
        return SendClientMessage(playerid, 0xFF0000FF, "ERROR: {FFFFFF}Kamu sedang mengetes progress bar V2!");
        
    SetPVarInt(playerid, "pTestProg2", 1);
    ApplyAnimation(playerid, "CHAINSAW", "WEAPON_csaw", 4.1, 1, 0, 0, 1, 0, 1);
    
     // UI: ProcessV1 or ProcessV2 (playerid, duration_seconds, "Module Description", "Module Header");
    ProcessV2(playerid, 10, "Menambang_Batu..", "Test_Miner_V2");
    return 1;
}

// Callbacks

public OnLSCProgbarFinish(playerid)
{
    if (GetPVarInt(playerid, "pTestProg1") == 1)
    {
        ClearAnimations(playerid);
        SendClientMessage(playerid, 0x00FF00FF, "SYSTEM: {FFFFFF}Progress bar V1 selesai! 1x Batu didapatkan!");
        DeletePVar(playerid, "pTestProg1");
    }
    else if (GetPVarInt(playerid, "pTestProg2") == 1)
    {
        ClearAnimations(playerid);
        SendClientMessage(playerid, 0x00FF00FF, "SYSTEM: {FFFFFF}Progress bar V2 selesai! 1x Besi didapatkan!");
        DeletePVar(playerid, "pTestProg2");
    }
    return 1;
}

public OnLSCProgbarCancel(playerid)
{
    if (GetPVarInt(playerid, "pTestProg1") == 1)
    {
        ClearAnimations(playerid);
        SendClientMessage(playerid, 0xFF0000FF, "SYSTEM: {FFFFFF}Progress bar V1 dibatalkan!");
        DeletePVar(playerid, "pTestProg1");
    }
    else if (GetPVarInt(playerid, "pTestProg2") == 1)
    {
        ClearAnimations(playerid);
        SendClientMessage(playerid, 0xFF0000FF, "SYSTEM: {FFFFFF}Progress bar V2 dibatalkan!");
        DeletePVar(playerid, "pTestProg2");
    }
    return 1;
}
```

---

<br>

<div align="center">
  <b>Credits</b><br>
  Textdraw Design V1 by <b>[kyomoto](https://github.com/KyeeS)</b><br>
  Textdraw Design V2 & Development by <b>[Apies](https://github.com/apies13)</b><br>
</div>
