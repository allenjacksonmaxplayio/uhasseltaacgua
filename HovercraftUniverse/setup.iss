[Setup]
OutputDir=bin\installer
Compression=lzma/ultra64
AppName=Hovercraft Universe
AppVerName=Hovercraft Universe v0.1
DefaultDirName={pf}\HovercraftUniverse
DefaultGroupName=Hovercraft Universe
AlwaysShowDirOnReadyPage=true
UninstallDisplayName=Hovercraft Universe
AppVersion=0.1
AppID={{3F2DDF97-F798-426F-81C7-2C9D4A6EAB05}
UninstallDisplayIcon={app}\HovercraftUniverse.exe
AllowNoIcons=true
VersionInfoCompany=UA
VersionInfoDescription=Hovercraft Universe
VersionInfoCopyright=Hovercraft Universe
VersionInfoProductName=Hovercraft Universe
AppPublisher=Hovercraft Universe
AppPublisherURL=http://uhasseltaacgua.googlecode.com/
AppSupportURL=http://uhasseltaacgua.googlecode.com/
AppUpdatesURL=http://uhasseltaacgua.googlecode.com/
OutputBaseFilename=setup
WizardImageFile=bin\installer\setup-large.bmp
WizardImageBackColor=clMaroon
WizardSmallImageFile=bin\installer\setup-small.bmp
SetupIconFile=bin\installer\HovercraftUniverse.ico
VersionInfoVersion=0.1
VersionInfoTextVersion=0.1
VersionInfoProductVersion=0.1
PrivilegesRequired=none
[Files]
Source: bin\release\HovercraftUniverse.exe; DestDir: {app}
Source: bin\installer\HovercraftUniverse.ini; DestDir: {app}
Source: bin\release\lua5.1.dll; DestDir: {app}
Source: bin\release\lua51.dll; DestDir: {app}
Source: bin\release\fmodex.dll; DestDir: {app}
Source: bin\release\Hikari.dll; DestDir: {app}
Source: bin\release\fmod_event.dll; DestDir: {app}
Source: bin\release\OgreMain.dll; DestDir: {app}
Source: bin\release\OIS.dll; DestDir: {app}
Source: bin\release\zoidcom_vc.dll; DestDir: {app}
Source: data\.svn\prop-base\cg.dll.svn-base; DestDir: {app}\data\.svn\prop-base; Attribs: readonly
Source: data\.svn\prop-base\hkVisualDebugger.exe.svn-base; DestDir: {app}\data\.svn\prop-base; Attribs: readonly
Source: data\.svn\text-base\cg.dll.svn-base; DestDir: {app}\data\.svn\text-base; Attribs: readonly
Source: data\.svn\text-base\engine_settings.cfg.svn-base; DestDir: {app}\data\.svn\text-base; Attribs: readonly
Source: data\.svn\text-base\hkVisualDebugger.exe.svn-base; DestDir: {app}\data\.svn\text-base; Attribs: readonly
Source: data\.svn\text-base\plugins_debug.cfg.svn-base; DestDir: {app}\data\.svn\text-base; Attribs: readonly
Source: data\.svn\text-base\plugins_release.cfg.svn-base; DestDir: {app}\data\.svn\text-base; Attribs: readonly
Source: data\.svn\text-base\resources.cfg.svn-base; DestDir: {app}\data\.svn\text-base; Attribs: readonly
Source: data\.svn\all-wcprops; DestDir: {app}\data\.svn; Attribs: readonly
Source: data\.svn\dir-prop-base; DestDir: {app}\data\.svn; Attribs: readonly
Source: data\.svn\entries; DestDir: {app}\data\.svn; Attribs: readonly
Source: data\controls\.svn\text-base\Controls.ini.svn-base; DestDir: {app}\data\controls\.svn\text-base; Attribs: readonly
Source: data\controls\.svn\all-wcprops; DestDir: {app}\data\controls\.svn; Attribs: readonly
Source: data\controls\.svn\entries; DestDir: {app}\data\controls\.svn; Attribs: readonly
Source: data\controls\Controls.ini; DestDir: {app}\data\controls
Source: data\entities\.svn\text-base\Entities.ini.svn-base; DestDir: {app}\data\entities\.svn\text-base; Attribs: readonly
Source: data\entities\.svn\all-wcprops; DestDir: {app}\data\entities\.svn; Attribs: readonly
Source: data\entities\.svn\entries; DestDir: {app}\data\entities\.svn; Attribs: readonly
Source: data\entities\Entities.ini; DestDir: {app}\data\entities
Source: data\gui\.svn\prop-base\background.swf.svn-base; DestDir: {app}\data\gui\.svn\prop-base; Attribs: readonly
Source: data\gui\.svn\prop-base\chat.swf.svn-base; DestDir: {app}\data\gui\.svn\prop-base; Attribs: readonly
Source: data\gui\.svn\prop-base\direction.swf.svn-base; DestDir: {app}\data\gui\.svn\prop-base; Attribs: readonly
Source: data\gui\.svn\prop-base\lapTimer.swf.svn-base; DestDir: {app}\data\gui\.svn\prop-base; Attribs: readonly
Source: data\gui\.svn\prop-base\loader.swf.svn-base; DestDir: {app}\data\gui\.svn\prop-base; Attribs: readonly
Source: data\gui\.svn\prop-base\lobby.swf.svn-base; DestDir: {app}\data\gui\.svn\prop-base; Attribs: readonly
Source: data\gui\.svn\prop-base\menuButton.swf.svn-base; DestDir: {app}\data\gui\.svn\prop-base; Attribs: readonly
Source: data\gui\.svn\prop-base\messagebox.swf.svn-base; DestDir: {app}\data\gui\.svn\prop-base; Attribs: readonly
Source: data\gui\.svn\prop-base\position.swf.svn-base; DestDir: {app}\data\gui\.svn\prop-base; Attribs: readonly
Source: data\gui\.svn\prop-base\serverMenu.swf.svn-base; DestDir: {app}\data\gui\.svn\prop-base; Attribs: readonly
Source: data\gui\.svn\prop-base\speedometer.swf.svn-base; DestDir: {app}\data\gui\.svn\prop-base; Attribs: readonly
Source: data\gui\.svn\prop-base\title.swf.svn-base; DestDir: {app}\data\gui\.svn\prop-base; Attribs: readonly
Source: data\gui\.svn\text-base\background.swf.svn-base; DestDir: {app}\data\gui\.svn\text-base; Attribs: readonly
Source: data\gui\.svn\text-base\chat.swf.svn-base; DestDir: {app}\data\gui\.svn\text-base; Attribs: readonly
Source: data\gui\.svn\text-base\direction.swf.svn-base; DestDir: {app}\data\gui\.svn\text-base; Attribs: readonly
Source: data\gui\.svn\text-base\GUIConfig.xml.svn-base; DestDir: {app}\data\gui\.svn\text-base; Attribs: readonly
Source: data\gui\.svn\text-base\lapTimer.swf.svn-base; DestDir: {app}\data\gui\.svn\text-base; Attribs: readonly
Source: data\gui\.svn\text-base\loader.swf.svn-base; DestDir: {app}\data\gui\.svn\text-base; Attribs: readonly
Source: data\gui\.svn\text-base\lobby.swf.svn-base; DestDir: {app}\data\gui\.svn\text-base; Attribs: readonly
Source: data\gui\.svn\text-base\menuButton.swf.svn-base; DestDir: {app}\data\gui\.svn\text-base; Attribs: readonly
Source: data\gui\.svn\text-base\messagebox.swf.svn-base; DestDir: {app}\data\gui\.svn\text-base; Attribs: readonly
Source: data\gui\.svn\text-base\position.swf.svn-base; DestDir: {app}\data\gui\.svn\text-base; Attribs: readonly
Source: data\gui\.svn\text-base\serverMenu.swf.svn-base; DestDir: {app}\data\gui\.svn\text-base; Attribs: readonly
Source: data\gui\.svn\text-base\speedometer.swf.svn-base; DestDir: {app}\data\gui\.svn\text-base; Attribs: readonly
Source: data\gui\.svn\text-base\title.swf.svn-base; DestDir: {app}\data\gui\.svn\text-base; Attribs: readonly
Source: data\gui\.svn\all-wcprops; DestDir: {app}\data\gui\.svn; Attribs: readonly
Source: data\gui\.svn\entries; DestDir: {app}\data\gui\.svn; Attribs: readonly
Source: data\gui\background.swf; DestDir: {app}\data\gui
Source: data\gui\chat.swf; DestDir: {app}\data\gui
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
Source: data\hovercraft\.svn\prop-base\HippyCraft.hkx.svn-base; DestDir: {app}\data\hovercraft\.svn\prop-base; Attribs: readonly
Source: data\hovercraft\.svn\prop-base\hover1.hkx.svn-base; DestDir: {app}\data\hovercraft\.svn\prop-base; Attribs: readonly
Source: data\hovercraft\.svn\prop-base\hover1.skeleton.svn-base; DestDir: {app}\data\hovercraft\.svn\prop-base; Attribs: readonly
Source: data\hovercraft\.svn\text-base\HippyCraft.hkx.svn-base; DestDir: {app}\data\hovercraft\.svn\text-base; Attribs: readonly
Source: data\hovercraft\.svn\text-base\HippyCraft.scene.svn-base; DestDir: {app}\data\hovercraft\.svn\text-base; Attribs: readonly
Source: data\hovercraft\.svn\text-base\hover1.hkx.svn-base; DestDir: {app}\data\hovercraft\.svn\text-base; Attribs: readonly
Source: data\hovercraft\.svn\text-base\hover1.scene.svn-base; DestDir: {app}\data\hovercraft\.svn\text-base; Attribs: readonly
Source: data\hovercraft\.svn\text-base\hover1.skeleton.svn-base; DestDir: {app}\data\hovercraft\.svn\text-base; Attribs: readonly
Source: data\hovercraft\.svn\all-wcprops; DestDir: {app}\data\hovercraft\.svn; Attribs: readonly
Source: data\hovercraft\.svn\entries; DestDir: {app}\data\hovercraft\.svn; Attribs: readonly
Source: data\hovercraft\materials\.svn\all-wcprops; DestDir: {app}\data\hovercraft\materials\.svn; Attribs: readonly
Source: data\hovercraft\materials\.svn\entries; DestDir: {app}\data\hovercraft\materials\.svn; Attribs: readonly
Source: data\hovercraft\materials\scripts\.svn\text-base\HippyCraft.material.svn-base; DestDir: {app}\data\hovercraft\materials\scripts\.svn\text-base; Attribs: readonly
Source: data\hovercraft\materials\scripts\.svn\text-base\hover1.material.svn-base; DestDir: {app}\data\hovercraft\materials\scripts\.svn\text-base; Attribs: readonly
Source: data\hovercraft\materials\scripts\.svn\all-wcprops; DestDir: {app}\data\hovercraft\materials\scripts\.svn; Attribs: readonly
Source: data\hovercraft\materials\scripts\.svn\entries; DestDir: {app}\data\hovercraft\materials\scripts\.svn; Attribs: readonly
Source: data\hovercraft\materials\scripts\HippyCraft.material; DestDir: {app}\data\hovercraft\materials\scripts
Source: data\hovercraft\materials\scripts\hover1.material; DestDir: {app}\data\hovercraft\materials\scripts
Source: data\hovercraft\materials\textures\.svn\prop-base\cogsmetallic.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\prop-base\hippycraftbody.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\prop-base\hovercogscabin.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\prop-base\hovercraftbody.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\prop-base\seat.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\prop-base\steeringwheel.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\prop-base\tires.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\text-base\cogsmetallic.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\text-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\text-base\hippycraftbody.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\text-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\text-base\hovercogscabin.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\text-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\text-base\hovercraftbody.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\text-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\text-base\seat.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\text-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\text-base\steeringwheel.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\text-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\text-base\tires.jpg.svn-base; DestDir: {app}\data\hovercraft\materials\textures\.svn\text-base; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\all-wcprops; DestDir: {app}\data\hovercraft\materials\textures\.svn; Attribs: readonly
Source: data\hovercraft\materials\textures\.svn\entries; DestDir: {app}\data\hovercraft\materials\textures\.svn; Attribs: readonly
Source: data\hovercraft\materials\textures\cogsmetallic.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\materials\textures\hippycraftbody.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\materials\textures\hovercogscabin.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\materials\textures\hovercraftbody.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\materials\textures\seat.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\materials\textures\steeringwheel.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\materials\textures\tires.jpg; DestDir: {app}\data\hovercraft\materials\textures
Source: data\hovercraft\models\.svn\prop-base\hippycraft.mesh.svn-base; DestDir: {app}\data\hovercraft\models\.svn\prop-base; Attribs: readonly
Source: data\hovercraft\models\.svn\prop-base\hover1.mesh.svn-base; DestDir: {app}\data\hovercraft\models\.svn\prop-base; Attribs: readonly
Source: data\hovercraft\models\.svn\text-base\hippycraft.mesh.svn-base; DestDir: {app}\data\hovercraft\models\.svn\text-base; Attribs: readonly
Source: data\hovercraft\models\.svn\text-base\hover1.mesh.svn-base; DestDir: {app}\data\hovercraft\models\.svn\text-base; Attribs: readonly
Source: data\hovercraft\models\.svn\all-wcprops; DestDir: {app}\data\hovercraft\models\.svn; Attribs: readonly
Source: data\hovercraft\models\.svn\entries; DestDir: {app}\data\hovercraft\models\.svn; Attribs: readonly
Source: data\hovercraft\models\hippycraft.mesh; DestDir: {app}\data\hovercraft\models
Source: data\hovercraft\models\hover1.mesh; DestDir: {app}\data\hovercraft\models
Source: data\hovercraft\HippyCraft.hkx; DestDir: {app}\data\hovercraft
Source: data\hovercraft\HippyCraft.scene; DestDir: {app}\data\hovercraft
Source: data\hovercraft\hover1.hkx; DestDir: {app}\data\hovercraft
Source: data\hovercraft\hover1.scene; DestDir: {app}\data\hovercraft
Source: data\hovercraft\hover1.skeleton; DestDir: {app}\data\hovercraft
Source: data\levels\.svn\prop-base\SimpleTrack.hkx.svn-base; DestDir: {app}\data\levels\.svn\prop-base; Attribs: readonly
Source: data\levels\.svn\text-base\DummyPath.path.svn-base; DestDir: {app}\data\levels\.svn\text-base; Attribs: readonly
Source: data\levels\.svn\text-base\SimpleTrack.hkx.svn-base; DestDir: {app}\data\levels\.svn\text-base; Attribs: readonly
Source: data\levels\.svn\text-base\SimpleTrack.scene.svn-base; DestDir: {app}\data\levels\.svn\text-base; Attribs: readonly
Source: data\levels\.svn\all-wcprops; DestDir: {app}\data\levels\.svn; Attribs: readonly
Source: data\levels\.svn\entries; DestDir: {app}\data\levels\.svn; Attribs: readonly
Source: data\levels\materials\.svn\all-wcprops; DestDir: {app}\data\levels\materials\.svn; Attribs: readonly
Source: data\levels\materials\.svn\entries; DestDir: {app}\data\levels\materials\.svn; Attribs: readonly
Source: data\levels\materials\programs\.svn\text-base\asteroidPS.cg.svn-base; DestDir: {app}\data\levels\materials\programs\.svn\text-base; Attribs: readonly
Source: data\levels\materials\programs\.svn\text-base\asteroidVS.cg.svn-base; DestDir: {app}\data\levels\materials\programs\.svn\text-base; Attribs: readonly
Source: data\levels\materials\programs\.svn\all-wcprops; DestDir: {app}\data\levels\materials\programs\.svn; Attribs: readonly
Source: data\levels\materials\programs\.svn\entries; DestDir: {app}\data\levels\materials\programs\.svn; Attribs: readonly
Source: data\levels\materials\programs\asteroidPS.cg; DestDir: {app}\data\levels\materials\programs
Source: data\levels\materials\programs\asteroidVS.cg; DestDir: {app}\data\levels\materials\programs
Source: data\levels\materials\scripts\.svn\text-base\asteroid.program.svn-base; DestDir: {app}\data\levels\materials\scripts\.svn\text-base; Attribs: readonly
Source: data\levels\materials\scripts\.svn\text-base\SimpleTrack.material.svn-base; DestDir: {app}\data\levels\materials\scripts\.svn\text-base; Attribs: readonly
Source: data\levels\materials\scripts\.svn\text-base\Terrain.rfx.svn-base; DestDir: {app}\data\levels\materials\scripts\.svn\text-base; Attribs: readonly
Source: data\levels\materials\scripts\.svn\all-wcprops; DestDir: {app}\data\levels\materials\scripts\.svn; Attribs: readonly
Source: data\levels\materials\scripts\.svn\entries; DestDir: {app}\data\levels\materials\scripts\.svn; Attribs: readonly
Source: data\levels\materials\scripts\asteroid.program; DestDir: {app}\data\levels\materials\scripts
Source: data\levels\materials\scripts\SimpleTrack.material; DestDir: {app}\data\levels\materials\scripts
Source: data\levels\materials\scripts\Terrain.rfx; DestDir: {app}\data\levels\materials\scripts
Source: data\levels\materials\textures\.svn\prop-base\brick_wall.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\concrete.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\dirt.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\front.png.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\grass.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\grass2.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\ice.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\jump-uvmap.png.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\jump.png.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\mud.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\Planet2GeomDiffuseMap.png.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\PlanetGeomDiffuseMap.png.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\road.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\rock.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\sand.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\TestAstrDiffuseMap1.tga.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\TestAstrDiffuseMap2.tga.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\prop-base\tower1.png.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\prop-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\brick_wall.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\concrete.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\dirt.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\front.png.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\grass.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\grass2.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\ice.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\jump-uvmap.png.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\jump.png.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\mud.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\Planet2GeomDiffuseMap.png.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\PlanetGeomDiffuseMap.png.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\road.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\rock.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\sand.jpg.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\TestAstrDiffuseMap1.tga.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\TestAstrDiffuseMap2.tga.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\text-base\tower1.png.svn-base; DestDir: {app}\data\levels\materials\textures\.svn\text-base; Attribs: readonly
Source: data\levels\materials\textures\.svn\all-wcprops; DestDir: {app}\data\levels\materials\textures\.svn; Attribs: readonly
Source: data\levels\materials\textures\.svn\entries; DestDir: {app}\data\levels\materials\textures\.svn; Attribs: readonly
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
Source: data\levels\models\.svn\prop-base\BoostGeom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\prop-base\CheckPoint0Geom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\prop-base\CheckPoint1Geom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\prop-base\FinishGeom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\prop-base\JumpGeo.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\prop-base\JumpGeo01.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\prop-base\JumpGeom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\prop-base\Planet1Geom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\prop-base\Planet2Geom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\prop-base\PlanetGeom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\prop-base\PlanetGeom01.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\prop-base\PlanetGeom02.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\prop-base\Speed.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\prop-base\StartGeom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\prop-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\BoostGeom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\CheckPoint0Geom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\CheckPoint1Geom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\FinishGeom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\JumpGeo.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\JumpGeo01.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\JumpGeom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\Planet1Geom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\Planet2Geom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\PlanetGeom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\PlanetGeom01.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\PlanetGeom02.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\Speed.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\text-base\StartGeom.mesh.svn-base; DestDir: {app}\data\levels\models\.svn\text-base; Attribs: readonly
Source: data\levels\models\.svn\all-wcprops; DestDir: {app}\data\levels\models\.svn; Attribs: readonly
Source: data\levels\models\.svn\entries; DestDir: {app}\data\levels\models\.svn; Attribs: readonly
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
Source: data\ogre\.svn\prop-base\cursor.png.svn-base; DestDir: {app}\data\ogre\.svn\prop-base; Attribs: readonly
Source: data\ogre\.svn\text-base\cursor.png.svn-base; DestDir: {app}\data\ogre\.svn\text-base; Attribs: readonly
Source: data\ogre\.svn\all-wcprops; DestDir: {app}\data\ogre\.svn; Attribs: readonly
Source: data\ogre\.svn\dir-prop-base; DestDir: {app}\data\ogre\.svn; Attribs: readonly
Source: data\ogre\.svn\entries; DestDir: {app}\data\ogre\.svn; Attribs: readonly
Source: data\ogre\cursor.png; DestDir: {app}\data\ogre
Source: data\plugins_debug\.svn\all-wcprops; DestDir: {app}\data\plugins_debug\.svn; Attribs: readonly
Source: data\plugins_debug\.svn\dir-prop-base; DestDir: {app}\data\plugins_debug\.svn; Attribs: readonly
Source: data\plugins_debug\.svn\entries; DestDir: {app}\data\plugins_debug\.svn; Attribs: readonly
Source: data\plugins_debug\Plugin_BSPSceneManager_d.dll; DestDir: {app}\data\plugins_debug
Source: data\plugins_debug\Plugin_CgProgramManager_d.dll; DestDir: {app}\data\plugins_debug
Source: data\plugins_debug\Plugin_OctreeSceneManager_d.dll; DestDir: {app}\data\plugins_debug
Source: data\plugins_debug\Plugin_OctreeZone_d.dll; DestDir: {app}\data\plugins_debug
Source: data\plugins_debug\Plugin_ParticleFX_d.dll; DestDir: {app}\data\plugins_debug
Source: data\plugins_debug\Plugin_PCZSceneManager_d.dll; DestDir: {app}\data\plugins_debug
Source: data\plugins_debug\RenderSystem_Direct3D10_d.dll; DestDir: {app}\data\plugins_debug
Source: data\plugins_debug\RenderSystem_Direct3D9_d.dll; DestDir: {app}\data\plugins_debug
Source: data\plugins_debug\RenderSystem_GL_d.dll; DestDir: {app}\data\plugins_debug
Source: data\plugins_release\.svn\all-wcprops; DestDir: {app}\data\plugins_release\.svn; Attribs: readonly
Source: data\plugins_release\.svn\dir-prop-base; DestDir: {app}\data\plugins_release\.svn; Attribs: readonly
Source: data\plugins_release\.svn\entries; DestDir: {app}\data\plugins_release\.svn; Attribs: readonly
Source: data\plugins_release\Plugin_BSPSceneManager.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\Plugin_CgProgramManager.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\Plugin_OctreeSceneManager.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\Plugin_OctreeZone.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\Plugin_ParticleFX.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\Plugin_PCZSceneManager.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\RenderSystem_Direct3D10.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\RenderSystem_Direct3D9.dll; DestDir: {app}\data\plugins_release
Source: data\plugins_release\RenderSystem_GL.dll; DestDir: {app}\data\plugins_release
Source: data\scripts\.svn\all-wcprops; DestDir: {app}\data\scripts\.svn; Attribs: readonly
Source: data\scripts\.svn\entries; DestDir: {app}\data\scripts\.svn; Attribs: readonly
Source: data\scripts\AI\.svn\text-base\Pathfinding.lua.svn-base; DestDir: {app}\data\scripts\AI\.svn\text-base; Attribs: readonly
Source: data\scripts\AI\.svn\text-base\SimpleAI.lua.svn-base; DestDir: {app}\data\scripts\AI\.svn\text-base; Attribs: readonly
Source: data\scripts\AI\.svn\text-base\Utils.lua.svn-base; DestDir: {app}\data\scripts\AI\.svn\text-base; Attribs: readonly
Source: data\scripts\AI\.svn\all-wcprops; DestDir: {app}\data\scripts\AI\.svn; Attribs: readonly
Source: data\scripts\AI\.svn\entries; DestDir: {app}\data\scripts\AI\.svn; Attribs: readonly
Source: data\scripts\AI\Pathfinding.lua; DestDir: {app}\data\scripts\AI
Source: data\scripts\AI\SimpleAI.lua; DestDir: {app}\data\scripts\AI
Source: data\scripts\AI\Utils.lua; DestDir: {app}\data\scripts\AI
Source: data\sound\.svn\prop-base\HovSound.fev.svn-base; DestDir: {app}\data\sound\.svn\prop-base; Attribs: readonly
Source: data\sound\.svn\prop-base\HovUniv.fsb.svn-base; DestDir: {app}\data\sound\.svn\prop-base; Attribs: readonly
Source: data\sound\.svn\text-base\HovSound.fev.svn-base; DestDir: {app}\data\sound\.svn\text-base; Attribs: readonly
Source: data\sound\.svn\text-base\HovSound.h.svn-base; DestDir: {app}\data\sound\.svn\text-base; Attribs: readonly
Source: data\sound\.svn\text-base\HovUniv.fsb.svn-base; DestDir: {app}\data\sound\.svn\text-base; Attribs: readonly
Source: data\sound\.svn\all-wcprops; DestDir: {app}\data\sound\.svn; Attribs: readonly
Source: data\sound\.svn\entries; DestDir: {app}\data\sound\.svn; Attribs: readonly
Source: data\sound\HovSound.fev; DestDir: {app}\data\sound
Source: data\sound\HovSound.h; DestDir: {app}\data\sound
Source: data\sound\HovUniv.fsb; DestDir: {app}\data\sound
Source: data\user\.svn\text-base\game.userdatatypes.xml.svn-base; DestDir: {app}\data\user\.svn\text-base; Attribs: readonly
Source: data\user\.svn\text-base\types.userdatatypes.xml.svn-base; DestDir: {app}\data\user\.svn\text-base; Attribs: readonly
Source: data\user\.svn\all-wcprops; DestDir: {app}\data\user\.svn; Attribs: readonly
Source: data\user\.svn\entries; DestDir: {app}\data\user\.svn; Attribs: readonly
Source: data\user\game.userdatatypes.xml; DestDir: {app}\data\user
Source: data\user\types.userdatatypes.xml; DestDir: {app}\data\user
Source: data\.ogre.cfg; DestDir: {app}\data\
Source: data\cg.dll; DestDir: {app}\data\
Source: data\engine_settings.cfg; DestDir: {app}\data\
Source: data\Flash.ocx; DestDir: {app}\data\; Attribs: readonly
Source: data\hkVisualDebugger.exe; DestDir: {app}\data\
Source: data\HovercraftUniverse.log; DestDir: {app}\data\
Source: data\ogre.cfg; DestDir: {app}\data\
Source: data\plugins_debug.cfg; DestDir: {app}\data\
Source: data\plugins_release.cfg; DestDir: {app}\data\
Source: data\resources.cfg; DestDir: {app}\data\
Source: data\Server.log; DestDir: {app}\data\
[Icons]
Name: {commondesktop}\Hovercraft Universe; Filename: {app}\HovercraftUniverse.exe; WorkingDir: {app}; IconFilename: {app}\HovercraftUniverse.exe; Comment: Play Hovercraft Universe; IconIndex: 0
Name: {commondesktop}\Hovercraft Universe Dedicated Server; Filename: {app}\HovercraftUniverse.exe; WorkingDir: {app}; IconFilename: {app}\HovercraftUniverse.exe; Comment: Hovercraft Universe Dedicated Server; Parameters: --server; IconIndex: 0
[Run]
Filename: {app}\HovercraftUniverse.exe; Description: Start playing Hovercraft Universe!; Flags: postinstall skipifsilent unchecked
[Dirs]
Name: {app}\data
