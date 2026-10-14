# AGENTS.md — Flyff-v21 (NukeZero Community Source)

> **Status:** Archived / Read-only release. Educational use only.
> **Source:** https://github.com/NukeZero/Flyff-v21
> **Local clone:** `E:\Game\Flyff-v21`

---

## 1. Project Overview

This is the full leaked source code of **Flyff v21** (NukeZero / Community edition),
the MMORPG that Dragon Crusade is built on. It contains **all** server executables,
the game client, build tools, Lua game scripts, item/map/skill data tables, and
a barebones SQL schema backup.

### 1.1 Scale

| Metric | Count |
|---|---|
| Total files | ~4 140 |
| C++ source (.cpp) | 1 772 files, ~1 355 596 lines |
| C++ headers (.h) | 2 368 files, ~620 795 lines |
| Lua scripts | 47 files, ~5 977 lines |
| Shaders (.fx) | 3 files, ~933 lines |
| **Total lines** | **~1 983 310** |

### 1.2 What's Inside

```
E:\Game\Flyff-v21\
├── Source/
│   ├── GameSource/
│   │   ├── all/                  ← Master solution (all80.sln) — 8 projects, Win32 only
│   │   ├── Neuz/                 ← GAME CLIENT (DirectX 9, MFC, Win32 GUI)
│   │   ├── WORLDSERVER/          ← Main game server
│   │   ├── LOGINSERVER/          ← Login/auth server
│   │   ├── AccountServer/        ← Account management server
│   │   ├── CacheServer/          ← Cache server
│   │   ├── Certifier/            ← Certificate / security server
│   │   ├── CORESERVER/           ← Core server
│   │   └── databaseserver/       ← Database interface server
│   ├── LibrarySource/
│   │   ├── library80.sln         ← Build FIRST (ReleaseDll|Win32) — 10 static/DLL libs
│   │   ├── common/               ← Shared types, game logic (item, skill, world, …)
│   │   ├── network/              ← Network protocol layer
│   │   ├── database/             ← SQL abstraction
│   │   ├── crypto/               ← Encryption / hashing
│   │   ├── thread/               ← Threading / sync primitives
│   │   ├── memory/               ← Memory allocators
│   │   ├── ui/                   ← Custom UI framework (non-MFC)
│   │   ├── dump/                 ← Crash dump handler
│   │   ├── logging/              ← Logging
│   │   ├── resource/             ← Resource loader
│   │   └── bugtrap/              ← BugTrap crash reporter (ThirdParty/BugTrap)
│   └── ToolSource/
│       ├── ScriptConvert/        ← Converts old text scripts to binary
│       ├── merge2/               ← Binary merger tool
│       ├── Cola_Net/             ← Network packet tool
│       ├── Daisy_Net/            ← NPCMaker dialogue tool
│       ├── Miranda_Net/          ← World editor / map tool
│       ├── Beast_Net/            ← Another editor tool
│       ├── Launcher/             ← Game launcher
│       ├── Updater/              ← Patcher/updater
│       ├── PatchClient*/         ← Client patcher
│       ├── FileEncryption_*/     ← File encryption tools
│       ├── SfxEditor_Net/        ← SFX editor
│       ├── Max*Exporter/         ← 3DS Max exporters
│       └── ProfileView/          ← Profiler viewer
├── Data/
│   ├── Config/                   ← Per-language filter/name config (14 locales)
│   ├── Program/                  ← .ini files for all 7 servers
│   ├── Resource/                 ← ⭐ THE GAME DATA (274 files)
│   │   ├── propItem.txt          ← Every item in the game
│   │   ├── propSkill.txt         ← Every skill
│   │   ├── propMover.txt         ← Every monster/NPC
│   │   ├── propQuest*.txt        ← Quest data
│   │   ├── expTable.inc          ← XP curve
│   │   ├── define*.h             ← Game constants/enums
│   │   ├── AI_Script.txt         ← Monster AI scripts
│   │   ├── NpcScript.txt         ← NPC quest dialogue scripts
│   │   ├── itemScript.lua        ← Item event scripts
│   │   ├── WorldDialog.txt       ← World-server dialogue rules
│   │   ├── Text/                 ← UI text strings (all languages)
│   │   ├── NPC/                  ← NPC config files
│   │   ├── DropItem/             ← Drop tables
│   │   ├── Event/                ← Event definitions
│   │   ├── LuaFunc/              ← Lua function wrappers
│   │   └── *.fx                  ← HLSL shaders (water, blur, shadow)
│   └── script/
│       ├── databaseserver.ini
│       └── WorldServer.ini
├── ThirdParty/
│   ├── BugTrap/                  ← Crash reporting
│   ├── directX/                  ← DirectX 9 SDK headers/libs
│   ├── Lua/                      ← Lua 5.x (scripting engine)
│   ├── miles/                    ← Miles Sound System (mss32.dll / mssogg.asi)
│   ├── boost/                    ← Boost (SPIR-V compiler / misc)
│   └── json/                     ← JSON parser (nlohmann or similar)
├── sql/
│   ├── Account (Optional).sql   ← Account creation helper
│   └── *.bak                    ← Database backup templates
│       ├── ACCOUNT_DBF.bak
│       ├── CHARACTER_01_DBF.bak
│       ├── LOGGING_01_DBF.bak
│       └── RANKING_DBF.bak
├── FlyffPath.json               ← File mover config (build → Data/ layout)
└── README.md
```

---

## 2. Build Requirements

### 2.1 Mandatory

| Component | Version | Notes |
|---|---|---|
| Visual Studio | **2022 Community** (v17.x) | Community is free |
| Platform Toolset | **v145** (VS 2022) | Already set in .vcxproj files |
| Windows SDK | 10.0 | Already referenced |
| MSVC Runtime | v143/v145 C++ redistributable | Ships with VS 2022 |
| SQL Server | **2019** (Express or full) | LocalDB may work for testing |
| SQL Server Management Studio | Any recent version | For running the schema |
| Git | Any | Already cloned |

### 2.2 Third-Party Libraries (included in repo)

| Library | Location | Purpose |
|---|---|---|
| DirectX 9 SDK | `ThirdParty/directX/` | d3dx9, d3d9, dsound, dxerr9 headers+libs |
| Lua | `ThirdParty/Lua/` | Scripting engine (NPCs, quests, events, items) |
| Miles Sound System | `ThirdParty/miles/` | Audio (mss32.dll, mssogg.asi) |
| BugTrap | `ThirdParty/BugTrap/` | Crash dump generation |
| Boost | `ThirdParty/boost/` | SPIR-V cross-compiler |
| nlohmann/json | `ThirdParty/json/` | JSON parsing |

All third-party libs ship with the repo — **no external downloads needed.**

### 2.3 Not Included (you must supply)

| Component | Why not included | How to get |
|---|---|---|
| XTrap libraries (`XTrap*.lib/.dll`) | Anti-cheat SDK — licensed by GNS, not redistributable | Must be extracted from an existing Flyff/DC client, or stub out |
| GameGuard libraries (`NPGameLib.lib/.dll`) | Anti-cheat SDK — licensed by INCA Internet, not redistributable | Same — extract from a working client, or stub out |
| DirectX 9 end-user runtime | Windows doesn't ship D3DX9 anymore | Install [DirectX End-User Runtime (Jun 2010)](https://www.microsoft.com/en-us/download/details.aspx?id=8109) — this only needs to be on the **player's machine**, not the build machine |
| SQL Server database `*.mdf` files | Backup files exist but may not be current | Restore from `.bak` files or create fresh DB |

---

## 3. Build Order (Critical)

The build order is **strict** — libraries before servers, servers before client.

```
Step 1: LibrarySource\library80.sln
        Configuration: ReleaseDll | Win32
        Action:       Build Solution (F6)
        Output:       Bins\LibraryBins\Win32\*.lib / *.dll

Step 2: GameSource\all\all80.sln
        Configuration: Release | Win32
        Action:       Build Solution (F6)

        Internal build order within all80.sln:
          1. DatabaseServer   (depends on: library)
          2. AccountServer    (depends on: library)
          3. Certifier        (depends on: library)
          4. CoreServer       (depends: library)
          5. LoginServer      (depends: library)
          6. CacheServer      (depends: library)
          7. WorldServer      (depends: all servers + library)
          8. Neuz (CLIENT)    (depends: library + DirectX9 + Miles + Lua)

        Output: Bins\ServerBins\Win32\Release\*.exe
                Bins\ClientBins\Win32\Release\Neuz.exe
```

### Build order matters because:
- `library80.sln` output goes to `Bins\LibraryBins\Win32\` — all projects link against it
- `all80.sln` does **not** auto-build the libraries — build them first
- The game server projects depend on each other (WorldServer is the last one)
- `Neuz` (client) needs all library .libs + DirectX9 + audio + Lua

---

## 4. What Can Actually Build (Honest Assessment)

### ✅ Will Build (with minimal effort)
- **LibrarySource** (all 10 projects) — pure C++, no external deps beyond what's in-tree
- **DatabaseServer** — pure C++ + SQL client library
- **AccountServer** — pure C++
- **Certifier** — pure C++
- **CoreServer** — pure C++
- **LoginServer** — pure C++
- **CacheServer** — pure C++
- **WorldServer** — pure C++

### ⚠️ Will Compile But Won't Run (without workarounds)
- **Neuz (CLIENT)** — will compile but at runtime needs:
  - `XTrap*.dll` — anti-cheat, not in repo → game will crash on startup without it
  - `NPGameLib.dll` — GameGuard anti-cheat → same problem
  - `mss32.dll` + `mssogg.asi` — IN the repo (Data/Resource) but must be alongside Neuz.exe
  - A full set of game resource files (models .o3d, textures .dds, maps, effects)
  - A running server cluster to connect to

### ❌ Will Not Build Without Work
- **Neuz** IF you have a VS version older than 2022 — the project file requires v145
- **Lua scripts** need the ScriptConvert tool first — raw `.lua` files in Data/Resource/ must be compiled before the client reads them
- **Game data files** (`.inc`, `.txt`) need the `merge2` and `FileEncryption` tools to package into the binary format the client expects

### 🔴 Known Blockers to a Fully Working Client+Server

| Blocker | Details | Workaround |
|---|---|---|
| XTrap anti-cheat missing | No .lib/.dll in repo | Extract from existing Flyff client, or comment out XTrap init in Neuz.cpp / StdAfx.cpp |
| GameGuard missing | No .lib/.dll in repo | Extract from existing client, or stub out `NPGameLib.cpp` |
| No game resource .o3d/.dds models | Data/Resource has only scripts & configs | You need the actual game assets from a Flyff v21 client |
| SQL schema incomplete | Only `.bak` backups, no CREATE TABLE scripts | Restore .bak files, or find full CREATE scripts |
| ScriptConvert not run | Lua files need pre-processing | Build ToolSource/ScriptConvert, run on Data/Resource/ |
| Files not encrypted | `neuz.ini` references encrypted data | Run `merge2` / `FileEncrpytion_MFC` tools on the data directory |

---

## 5. How to Build (Step-by-Step)

```powershell
# ─── Prerequisites ───────────────────────────────────────────────────────────
# 1. Install Visual Studio 2022 Community with:
#    - "Desktop development with C++"
#    - Windows 10/11 SDK
#    - MSVC v143 - VS 2022 C++ x64/x86 build tools
# 2. Install SQL Server 2019 Express
# 3. Install SQL Server Management Studio (SSMS)
# 4. Install DirectX End-User Runtime (Jun 2010) — player side only
# 5. Open x86 Native Tools Command Prompt for VS 2022

# ─── Step 1: Build Libraries ────────────────────────────────────────────────
cd E:\Game\Flyff-v21\Source\LibrarySource
msbuild library80.sln /p:Configuration=ReleaseDll /p:Platform=Win32

# Output lands in: Bins\LibraryBins\Win32\

# ─── Step 2: Build Servers + Client ─────────────────────────────────────────
cd E:\Game\Flyff-v21\Source\GameSource\all
msbuild all80.sln /p:Configuration=Release /p:Platform=Win32

# Output lands in:
#   Bins\ServerBins\Win32\Release\1. AccountServer.exe
#   Bins\ServerBins\Win32\Release\2. Certifier.exe
#   Bins\ServerBins\Win32\Release\3. DatabaseServer.exe
#   Bins\ServerBins\Win32\Release\4. CoreServer.exe
#   Bins\ServerBins\Win32\Release\5. LoginServer.exe
#   Bins\ServerBins\Win32\Release\6. CacheServer.exe
#   Bins\ServerBins\Win32\Release\7. WorldServer.exe
#   Bins\ClientBins\Win32\Release\Neuz.exe

# ─── Step 3: Move Files Into Place ──────────────────────────────────────────
# Copy server exes to Data\Program\ (renamed as shown in FlyffPath.json)
# Copy Neuz.exe to Client\Neuz.exe
# Copy Data\Resource\* next to Neuz.exe (or set paths in WorldServer.ini)

# ─── Step 4: Prepare Database ────────────────────────────────────────────────
# In SSMS:
#   RESTORE DATABASE ACCOUNT_DBF FROM DISK = '...\sql\ACCOUNT_DBF.bak'
#   RESTORE DATABASE CHARACTER_01_DBF FROM DISK = '...\sql\CHARACTER_01_DBF.bak'
#   RESTORE DATABASE LOGGING_01_DBF FROM DISK = '...\sql\LOGGING_01_DBF.bak'
#   RESTORE DATABASE RANKING_DBF FROM DISK = '...\sql\RANKING_DBF.bak'
# Then run: sql\Account (Optional).sql  to create a test account

# ─── Step 5: Configure ───────────────────────────────────────────────────────
# Edit Data\Program\WorldServer.ini:
#   Set CACHE_BIND_IP, Core, DB to your SQL Server IP
#   Uncomment any desired feature flags (PK, STEAL, GUILDCOMBAT, etc.)

# Data\script\WorldServer.ini — database connection string
# Data\script\databaseserver.ini — database connection string

# ─── Step 6: Run Server Cluster (in order) ───────────────────────────────────
# 1. Data\Program\3. Database.exe    (or DatabaseServer.exe directly)
# 2. Data\Program\1. Account.exe
# 3. Data\Program\4. Core.exe
# 4. Data\Program\2. Certifier.exe
# 5. Data\Program\5. Login.exe
# 6. Data\Program\6. Cache.exe
# 7. Data\Program\7. World.exe

# ─── Step 7: Run Client ──────────────────────────────────────────────────────
# Client\Neuz.exe
# (must be on same machine or have network access to the servers)
```

---

## 6. Architecture (Server Cluster)

```
                    ┌─────────────────┐
                    │   Neuz (Client) │
                    └────────┬────────┘
                             │ TCP
                    ┌────────▼────────┐
                    │  LoginServer     │  ← Auth, character list
                    └────────┬────────┘
                             │
              ┌──────────────┼──────────────┐
       ┌──────▼──────┐ ┌─────▼─────┐ ┌─────▼─────┐
       │ AccountServer│ │Certifier │ │ CoreServer│  ← Account mgmt, security, core relay
       └─────────────┘ └──────────┘ └───────────┘
                             │
                    ┌────────▼────────┐
                    │  WorldServer     │  ← Main game logic, NPCs, combat, quests
                    └────────┬────────┘
                             │
                    ┌────────▼────────┐
                    │ DatabaseServer   │  ← SQL relay
                    └────────┬────────┘
                             │
                    ┌────────▼────────┐
                    │  SQL Server 2019 │
                    │  ACCOUNT_DBF     │
                    │  CHARACTER_01_DBF│
                    │  LOGGING_01_DBF  │
                    │  RANKING_DBF     │
                    └──────────────────┘

                    ┌─────────────────┐
                    │  CacheServer     │  ← Static data cache (items, skills, etc.)
                    └─────────────────┘
```

---

## 7. Key Technical Details

| Aspect | Detail |
|---|---|
| Language | C++17 (stdcpp17), MBCS (MultiByte Character Set) |
| Platform | **Win32/x86 only** — all .sln files are `Release|Win32` |
| Toolset | MSVC v145 (VS 2022) |
| Graphics API | **DirectX 9** (d3dx9.lib, dsound.lib, dxerr9.lib) |
| Audio | Miles Sound System 6.x (mss32.dll) + OGG (mssogg.asi) |
| Scripting | Lua 5.x (NPCs, quests, events, item logic) |
| Networking | Custom TCP/UDP (LibrarySource/network/) + RakNet-style packet system |
| Anti-cheat | XTrap (GNS) + GameGuard (INCA) — both in header references |
| UI framework | Custom MFC-influenced windowing (`_Interface/*Wnd*.cpp`) |
| Crash reporting | BugTrap (ThirdParty/BugTrap/) |
| Build output | `Bins\ClientBins\Win32\Release\` + `Bins\ServerBins\Win32\Release\` |
| C++ standard | C++17 (`/std:c++17`) |
| Character set | Multi-byte (not Unicode) — ANSI strings throughout |

---

## 8. What You Can Actually Modify (Even Without Building)

| Area | How | Effort |
|---|---|---|
| Game balance (XP rates, drop rates, skill values) | Edit `.txt` / `.inc` / `.lua` files in `Data/Resource/` then run `merge2` + `FileEncryption` tools | Low |
| Item stats, skills, monsters | Edit `propItem.txt`, `propSkill.txt`, `propMover.txt` etc. | Low |
| Quests & NPC dialogue | Edit `NpcScript.txt`, `propQuest*.inc` | Low–Med |
| Server rules (PK, guild war, events) | Edit `Data/Program/WorldServer.ini` flags | Trivial |
| Map data | Requires 3DS Max + the Miranda/Beast/Daisy exporter tools | Med–High |
| Custom quests/events | Write `.lua` scripts in `Data/Resource/Event/`, `Data/Resource/LuaFunc/` | Med |
| Client UI / hotkey system | Edit `Source/GameSource/_Interface/WndTaskBar.cpp`, `WndOptionGame.cpp` | High |
| New 3D models / textures | Requires 3DS Max 5–2009 + exporters | High |

---

## 9. Relationship to Dragon Crusade

Dragon Crusade is built ON TOP of this codebase. Your DC client contains all of these
custom additions NOT present in vanilla v21:

- `FlySystem` (flight mode)
- `BeginnerMode` (soft difficulty)
- `BossSelection` (boss targeting mode)
- `DragonMinimized` (mount UI)
- `RenderDmgMeterNew` (new DPS meter)
- `UseOldBuffRendering` (legacy UI toggle)
- `ResizeableInventory` (draggable windows)
- New maps: Dragon Island, Fortress, Frost Dragon's Gate, Crystal Labyrinth, etc.
- `Dragon Rank` system (entirely new progression tier, areas from Fire Land to Krono)
- Custom pets: Venusaur Mega Shiny, Shen Long, Faceless Rex, etc.
- Custom cloaks: Twin Dragons, Wisp, Majesty, etc.
- New dungeons: Aminuskrypta, Clockworks, Red/Blue/Green Meteo, Cursed Aminus, etc.
- Dragon Cloak quest system
- Kill Counter Shop
- Custom join/level letter system (Text/Letter_*.txt)
- WebView2 integration (modern browser in-game)
- `AlternativePatcher.exe` (custom patcher)

None of this exists in the v21 source. DC's server-side logic is **completely separate
and proprietary** — the server binary is not available.

---

## 10. Bottom Line

| Goal | Difficulty | Notes |
|---|---|---|
| Build all libraries (ReleaseDll) | 🟢 Easy | `msbuild library80.sln` — just needs VS 2022 |
| Build all server .exes | 🟡 Medium | Same, but SQL Server must be installed (even if unused) |
| Build Neuz.exe (client) | 🟡 Medium | Will compile; won't run without XTrap/GameGuard stubs + game assets |
| Get a working vanilla Flyff v21 server | 🟠 Hard | Needs SQL restore + all 7 servers in correct order + network config |
| Get the client connecting | 🔴 Very Hard | Needs XTrap/GameGuard + full resource tree + encryption keys + running server |
| Add a new monster/quest/lua event | 🟢–🟡 Easy | Edit data files, run merge tools |
| Modify client code (UI, input, rendering) | 🟠 Hard | Needs full rebuild + anti-cheat workaround + resource pipeline |
| Port Dragon Crusade content into this | 🔴 Very Hard | DC's server logic, custom systems, and content are not in this codebase |
| Full DC private server from scratch | ⬛ Impossible alone | Multi-year MMO dev project; DC owner holds the server-side IP |

The most useful path forward with this codebase is:
1. Read and understand the Lua game scripts
2. Edit item/skill/monster data tables
3. Build the server cluster for a vanilla Flyff v21 world
4. Use DC's **existing** client against your own server (protocol-compatible? needs testing)

---

# Reversa

> Framework de Engenharia Reversa instalado neste projeto.

## Como usar

Use o fluxo adequado no chat:

- `reversa` — descobrir e documentar um sistema existente
- `reversa-new` — criar PRD e specs para um projeto novo
- `reversa-forward` — implementar ou evoluir código a partir das specs
- `reversa-migrate` — planejar a migração de um sistema legado
- `reversa-docs` — gerar o mini-site visual da documentação
- `reversa-agents-help` — consultar o catálogo completo de agentes

## Comportamento ao ativar

Quando o usuário digitar `reversa` sozinho em uma mensagem:

1. Ative o skill `reversa` disponível em `.agents/skills/reversa/SKILL.md`
2. Leia o SKILL.md na íntegra e siga exatamente as instruções do Reversa

## Regra não-negociável

Por padrão, nunca apague, modifique ou sobrescreva arquivos pré-existentes do projeto legado:
o Reversa escreve apenas em `.reversa/`, `_reversa_sdd/`, `_reversa_docs/`, `_reversa_forward/`, `_reversa_bugs/` e `_reversa_refactor/`.
A única exceção é a política configurável abaixo, controlada exclusivamente pelo usuário.

Antes de criar, modificar ou apagar qualquer arquivo fora das pastas próprias do Reversa, leia `.reversa/reversa-config.json` e obedeça ao resultado:

- Arquivo ausente, JSON inválido ou campo com tipo errado: trate como `allowLegacyEdits: false` (falha segura, nenhuma escrita fora das pastas do Reversa).
- `allowLegacyEdits: false`: recuse a escrita, informando o caminho recusado, o estado atual da config e o que o usuário deve editar para liberar.
- `allowLegacyEdits: true` com `allowedPaths` não vazio: escreva apenas em caminhos que casem com algum glob da lista (globs relativos à raiz do projeto, com `/`, suportando `*` e `**`).
- `allowLegacyEdits: true` com `allowedPaths` vazio ou ausente: projeto liberado; avise uma vez por sessão que a liberação é irrestrita.

Nunca crie nem edite `.reversa/reversa-config.json` por iniciativa própria: pedido na conversa não é liberação implícita, alterações nesse arquivo são ato exclusivo do usuário.
