[Setup]
OutputDir=bin\installer
Compression=lzma/ultra64
AppName=Hovercraft Universe
AppVerName=Hovercraft Universe v0.2
DefaultDirName={pf}\HovercraftUniverse
DefaultGroupName=Hovercraft Universe
AlwaysShowDirOnReadyPage=true
UninstallDisplayName=Hovercraft Universe
AppVersion=0.2
AppID={{3F2DDF97-F798-426F-81C7-2C9D4A6EAB05}
UninstallDisplayIcon={app}\HovercraftUniverse.exe
AllowNoIcons=true
VersionInfoCompany=University of Antwerp
VersionInfoDescription=Hovercraft Universe
VersionInfoCopyright=Hovercraft Universe
AppPublisher=Hovercraft Universe
AppPublisherURL=http://uhasseltaacgua.googlecode.com/
AppSupportURL=http://uhasseltaacgua.googlecode.com/
AppUpdatesURL=http://uhasseltaacgua.googlecode.com/
OutputBaseFilename=HovercraftUniverseSetup
WizardImageFile=bin\installer\setup-large.bmp
WizardImageBackColor=clMaroon
WizardSmallImageFile=bin\installer\setup-small.bmp
;SetupIconFile=bin\installer\HovercraftUniverse.ico
VersionInfoVersion=0.2
VersionInfoTextVersion=0.2
PrivilegesRequired=none
[Icons]
Name: {commondesktop}\Hovercraft Universe; Filename: {app}\HovercraftUniverse.exe; WorkingDir: {app}; IconFilename: {app}\HovercraftUniverse.exe; Comment: Play Hovercraft Universe; IconIndex: 0
[Run]
Filename: {app}\HovercraftUniverse.exe; Description: Start playing Hovercraft Universe!; Flags: postinstall skipifsilent unchecked
[Files]
;Take the INIs from the bin\installer folder
Source: bin\installer\HovercraftUniverse.ini; DestDir: {app}
Source: bin\installer\Server.ini; DestDir: {app}

;Executables and DLL from the release folder
Source: bin\release\HovercraftUniverse.exe; DestDir: {app}
Source: bin\release\lua51.dll; DestDir: {app}
Source: bin\release\OgreMain.dll; DestDir: {app}
Source: bin\release\OIS.dll; DestDir: {app}
Source: bin\release\zoidcom_vc.dll; DestDir: {app}
Source: bin\release\fmod_event.dll; DestDir: {app}
Source: bin\release\fmodex.dll; DestDir: {app}
Source: bin\release\Hikari.dll; DestDir: {app}
Source: bin\release\lua5.1.dll; DestDir: {app}

;Data folder - without the debug plugins
Source: data\controls\Controls.ini; DestDir: {app}\data\controls
Source: data\entities\Entities.ini; DestDir: {app}\data\entities
Source: data\gui\background.swf; DestDir: {app}\data\gui
Source: data\gui\chat.swf; DestDir: {app}\data\gui
Source: data\gui\countdown.swf; DestDir: {app}\data\gui
Source: data\gui\direction.swf; DestDir: {app}\data\gui
Source: data\gui\GUIConfig.xml; DestDir: {app}\data\gui
Source: data\gui\lapTimer.swf; DestDir: {app}\data\gui
Source: data\gui\loader.swf; DestDir: {app}\data\gui
Source: data\gui\lobby.swf; DestDir: {app}\data\gui
Source: data\gui\menuButton.swf; DestDir: {app}\data\gui
Source: data\gui\messagebox.swf; DestDir: {app}\data\gui
Source: data\gui\position.swf; DestDir: {app}\data\gui
Source: data\gui\serverMenu.swf; DestDir: {app}\data\gui
Source: data\gui\speedometer.swf; DestDir: {app}\data\gui
Source: data\gui\title.swf; DestDir: {app}\data\gui
Source: data\hovercraft\materials\scripts\HippyCraft.material; DestDir: {app}\data\hovercraft\materials\scripts
Source: data\hovercraft\materials\scripts\hover1.material; DestDir: {app}\data\hovercraft\materials\scripts
Source: data\hovercraft\materials\textures\cogsmetallic.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\materials\textures\hippycraftbody.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\materials\textures\hovercogscabin.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\materials\textures\hovercraftbody.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\materials\textures\seat.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\materials\textures\steeringwheel.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\materials\textures\tires.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\models\hippycraft.mesh; DestDir: {app}\data\hovercraft\models
Source: data\hovercraft\models\hover1.mesh; DestDir: {app}\data\hovercraft\models
Source: data\hovercraft\HippyCraft.hkx; DestDir: {app}\data\hovercraft
Source: data\hovercraft\HippyCraft.scene; DestDir: {app}\data\hovercraft
Source: data\hovercraft\hover1.hkx; DestDir: {app}\data\hovercraft
Source: data\hovercraft\hover1.scene; DestDir: {app}\data\hovercraft
Source: data\hovercraft\hover1.skeleton; DestDir: {app}\data\hovercraft
Source: data\levels\materials\programs\asteroidPS.cg; DestDir: {app}\data\levels\materials\programs
Source: data\levels\materials\programs\asteroidVS.cg; DestDir: {app}\data\levels\materials\programs
Source: data\levels\materials\scripts\asteroid.program; DestDir: {app}\data\levels\materials\scripts
Source: data\levels\materials\scripts\SimpleTrack.material; DestDir: {app}\data\levels\materials\scripts
Source: data\levels\materials\scripts\Terrain.rfx; DestDir: {app}\data\levels\materials\scripts
Source: data\levels\materials\textures\brick_wall.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\concrete.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\dirt.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\front.png; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\grass.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\grass2.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\ice.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\jump-uvmap.png; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\jump.png; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\mud.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\Planet2GeomDiffuseMap.png; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\PlanetGeomDiffuseMap.png; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\road.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\rock.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\sand.jpg; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\TestAstrDiffuseMap1.tga; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\TestAstrDiffuseMap2.tga; DestDir: {app}\data\levels\materials\textures
Source: data\levels\materials\textures\tower1.png; DestDir: {app}\data\levels\materials\textures
Source: data\levels\models\BoostGeom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\CheckPoint0Geom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\CheckPoint1Geom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\FinishGeom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\JumpGeo.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\JumpGeo01.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\JumpGeom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\Planet1Geom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\Planet2Geom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\PlanetGeom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\PlanetGeom01.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\PlanetGeom02.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\Speed.mesh; DestDir: {app}\data\levels\models
Source: data\levels\models\StartGeom.mesh; DestDir: {app}\data\levels\models
Source: data\levels\DummyPath.path; DestDir: {app}\data\levels
Source: data\levels\SimpleTrack.hkx; DestDir: {app}\data\levels
Source: data\levels\SimpleTrack.scene; DestDir: {app}\data\levels
Source: data\levels\SimpleTrackManualPath.path; DestDir: {app}\data\levels
Source: data\levels\SimpleTrackRecorded.path; DestDir: {app}\data\levels
Source: data\ogre\fonts\badabb.ttf; DestDir: {app}\data\ogre\fonts
Source: data\ogre\fonts\Badaboom.fontdef; DestDir: {app}\data\ogre\fonts
Source: data\ogre\fonts\Lynx.fontdef; DestDir: {app}\data\ogre\fonts
Source: data\ogre\fonts\Lynx.ttf; DestDir: {app}\data\ogre\fonts
Source: data\ogre\fonts\solo5.ttf; DestDir: {app}\data\ogre\fonts
Source: data\ogre\fonts\StarWars.fontdef; DestDir: {app}\data\ogre\fonts
Source: data\ogre\materials\NicknameOverlay.material; DestDir: {app}\data\ogre\materials
Source: data\ogre\particle\bigflame.png; DestDir: {app}\data\ogre\particle
Source: data\ogre\particle\black.png; DestDir: {app}\data\ogre\particle
Source: data\ogre\particle\explosion.png; DestDir: {app}\data\ogre\particle
Source: data\ogre\particle\flare.png; DestDir: {app}\data\ogre\particle
Source: data\ogre\particle\flaretrail.png; DestDir: {app}\data\ogre\particle
Source: data\ogre\particle\PE_materials.material; DestDir: {app}\data\ogre\particle
Source: data\ogre\particle\PurpleFountain.particle; DestDir: {app}\data\ogre\particle
Source: data\ogre\particle\ring_flare.png; DestDir: {app}\data\ogre\particle
Source: data\ogre\particle\ring_flare2.png; DestDir: {app}\data\ogre\particle
Source: data\ogre\particle\smoke.png; DestDir: {app}\data\ogre\particle
Source: data\ogre\particle\Smokey.particle; DestDir: {app}\data\ogre\particle
Source: data\ogre\particle\streak.png; DestDir: {app}\data\ogre\particle
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
Source: data\scripts\AI\PathFollowing.lua; DestDir: {app}\data\scripts\AI
Source: data\scripts\AI\Utils.lua; DestDir: {app}\data\scripts\AI
Source: data\sound\HovSound.fev; DestDir: {app}\data\sound
Source: data\sound\HovSound.h; DestDir: {app}\data\sound
Source: data\sound\HovUniv.fsb; DestDir: {app}\data\sound
Source: data\user\game.userdatatypes.xml; DestDir: {app}\data\user
Source: data\user\types.userdatatypes.xml; DestDir: {app}\data\user
Source: data\cg.dll; DestDir: {app}\data\
Source: data\engine_settings.cfg; DestDir: {app}\data\
Source: data\Flash.ocx; DestDir: {app}\data\
Source: data\plugins_debug.cfg; DestDir: {app}\data\
Source: data\plugins_release.cfg; DestDir: {app}\data\
Source: data\resources.cfg; DestDir: {app}\data\
Source: data\SingleplayerServer.ini; DestDir: {app}\data\
[Dirs]
Name: {app}\data
Name: {app}\data\controls
Name: {app}\data\entities
Name: {app}\data\gui
Name: {app}\data\hovercraft
Name: {app}\data\hovercraft\materials
Name: {app}\data\hovercraft\materials\scripts
Name: {app}\data\hovercraft\materials\textures
Name: {app}\data\hovercraft\models
Name: {app}\data\levels
Name: {app}\data\levels\materials
Name: {app}\data\levels\materials\programs
Name: {app}\data\levels\materials\scripts
Name: {app}\data\levels\materials\textures
Name: {app}\data\levels\models
Name: {app}\data\ogre
Name: {app}\data\ogre\fonts
Name: {app}\data\ogre\materials
Name: {app}\data\ogre\particle
Name: {app}\data\plugins_debug
Name: {app}\data\plugins_release
Name: {app}\data\scripts
Name: {app}\data\scripts\AI
Name: {app}\data\sound
Name: {app}\data\user
