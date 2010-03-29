[Setup]
OutputDir=bin\installer
Compression=lzma/ultra64
MinVersion=0,5.0.2195
AppName=Hovercraft Universe
AppVerName=Hovercraft Universe v0.1
DefaultDirName={pf}\HovercraftUniverse
DefaultGroupName=Hovercraft Universe
AlwaysShowDirOnReadyPage=true
UninstallDisplayName=Hovercraft Universe
AppVersion=0.1
[Files]
Source: bin\release\HovercraftUniverse.exe; DestDir: {app}
Source: bin\installer\HovercraftUniverse.ini; DestDir: {app}
Source: bin\release\lua5.1.dll; DestDir: {app}
Source: bin\release\fmodex.dll; DestDir: {app}
Source: bin\release\Hikari.dll; DestDir: {app}
Source: bin\release\fmod_event.dll; DestDir: {app}
Source: bin\release\OgreMain.dll; DestDir: {app}
Source: bin\release\OIS.dll; DestDir: {app}
Source: bin\release\zoidcom_vc.dll; DestDir: {app}
Source: data\controls\Controls.ini; DestDir: {app}\data\controls
Source: data\gui\chat.swf; DestDir: {app}\data\gui
Source: data\gui\direction.swf; DestDir: {app}\data\gui
Source: data\gui\GUIConfig.xml; DestDir: {app}\data\gui
Source: data\gui\lapTimer.swf; DestDir: {app}\data\gui
Source: data\gui\lobby.swf; DestDir: {app}\data\gui
Source: data\gui\menuButton.swf; DestDir: {app}\data\gui
Source: data\gui\position.swf; DestDir: {app}\data\gui
Source: data\gui\serverMenu.swf; DestDir: {app}\data\gui
Source: data\gui\speedometer.swf; DestDir: {app}\data\gui
Source: data\gui\title.swf; DestDir: {app}\data\gui
Source: data\hovercraft\materials\scripts\hover1.material; DestDir: {app}\data\hovercraft\materials\scripts
Source: data\hovercraft\models\hover1.mesh; DestDir: {app}\data\hovercraft\models
Source: data\hovercraft\hover1.hkx; DestDir: {app}\data\hovercraft
Source: data\hovercraft\hover1.scene; DestDir: {app}\data\hovercraft
Source: data\levels\materials\programs\AlphaSplatTerrain.cg; DestDir: {app}\data\levels\materials\programs
Source: data\levels\materials\scripts\AlphaSplatTerrain.progam; DestDir: {app}\data\levels\materials\scripts
Source: data\levels\materials\scripts\AplhaSplatMaterial.material; DestDir: {app}\data\levels\materials\scripts
Source: data\levels\materials\scripts\SimpleTrack.material; DestDir: {app}\data\levels\materials\scripts
Source: data\levels\materials\textures\brick_wall.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\concrete.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\dirt.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\front.png; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\grass2.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\jump-uvmap.png; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\jump.png; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\PlanetGeomDiffuseMap.png; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\road.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\tower1.png; DestDir: {app}\data\levels\materials\textures
Source: data\levels\models\BoostGeom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\CheckPoint0Geom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\CheckPoint1Geom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\FinishGeom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\PlanetGeom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\StartGeom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\SimpleTrack.hkx; DestDir: {app}\data\levels
Source: data\levels\SimpleTrack.scene; DestDir: {app}\data\levels
Source: data\ogre\cursor.png; DestDir: {app}\data\ogre
Source: data\plugins_release\Plugin_BSPSceneManager.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\Plugin_CgProgramManager.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\Plugin_OctreeSceneManager.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\Plugin_OctreeZone.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\Plugin_ParticleFX.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\Plugin_PCZSceneManager.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\RenderSystem_Direct3D10.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\RenderSystem_Direct3D9.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\RenderSystem_GL.dll; DestDir: {app}\data\plugins_release
Source: data\scripts\AI\Pathfinding.lua; DestDir: {app}\data\scripts\AI
Source: data\scripts\AI\SimpleAI.lua; DestDir: {app}\data\scripts\AI
Source: data\scripts\AI\Utils.lua; DestDir: {app}\data\scripts\AI
Source: data\sound\HovSound.fev; DestDir: {app}\data\sound
Source: data\sound\HovSound.h; DestDir: {app}\data\sound
Source: data\sound\HovUniv.fsb; DestDir: {app}\data\sound
Source: data\user\game.userdatatypes.xml; DestDir: {app}\data\user
Source: data\user\types.userdatatypes.xml; DestDir: {app}\data\user
Source: data\cg.dll; DestDir: {app}\data\
Source: data\Flash.ocx; DestDir: {app}\data\; Attribs: readonly
Source: data\hkVisualDebugger.exe; DestDir: {app}\data\
Source: data\ogre.cfg; DestDir: {app}\data\
Source: data\plugins_release.cfg; DestDir: {app}\data\
Source: data\resources.cfg; DestDir: {app}\data\
[Dirs]
Name: {app}\data
Name: {app}\data\controls
Name: {app}\data\gui
Name: {app}\data\hovercraft
Name: {app}\data\hovercraft\materials
Name: {app}\data\hovercraft\materials\scripts
Name: {app}\data\hovercraft\models
Name: {app}\data\levels
Name: {app}\data\levels\materials
Name: {app}\data\levels\materials\programs
Name: {app}\data\levels\materials\scripts
Name: {app}\data\levels\materials\textures
Name: {app}\data\levels\models
Name: {app}\data\ogre
Name: {app}\data\plugins_release
Name: {app}\data\scripts
Name: {app}\data\scripts\AI
Name: {app}\data\sound
Name: {app}\data\user
[Icons]
Name: {commondesktop}\Hovercraft Universe; Filename: {app}\HovercraftUniverse.exe; WorkingDir: {app}; IconFilename: {app}\HovercraftUniverse.exe; Comment: Play Hovercraft Universe
Name: {commondesktop}\Hovercraft Universe Dedicated Server; Filename: {app}\HovercraftUniverse.exe; WorkingDir: {app}; IconFilename: {app}\HovercraftUniverse.exe; Comment: Hovercraft Universe Dedicated Server; Parameters: --server
[Run]
Filename: {app}\HovercraftUniverse.exe; Description: Start Hovercraft Universe; Flags: postinstall skipifsilent unchecked
