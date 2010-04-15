shaderfx_path = pathConfig.getCurrentProjectFolder()  + "\\shaderfx\\"
terrain_layer1_shader = shaderfx_path  + "terrain1.fx"
terrain_layer2_shader = shaderfx_path  + "terrain2.fx"
terrain_layers = #("","","","","","")

print terrain_layer1_shader
print terrain_layer2_shader

struct AsteroidInfo (
	/** Indices of the paint modifiers in the object modifier stack */
	vertexpaintidices = #(0,0),
	
	/** Number of paint layers, this is 0, 1 or 2 */
	vertexpaintlayers = 0,
	
	/** The Asteroid object **/
	asteroid = undefined,
	
	/** The ids of the color, viewport and ogre materials */
	color_material_id = undefined,	
	ogre_material_id = undefined,
	viewport_material_id = undefined,	
	
	fn createAlphaMap size outputfile = 
	(
		print "createAlphaMap"
		
		if color_material_id == undefined or viewport_material_id == undefined then (
			messageBox "No color material or viewport material found! Use create firts" title:"Error"			
		)
		else (		
			asteroid.material = currentMaterialLibrary[color_material_id]
			
			/* clean all previous */
			asteroid.iNodeBakeProperties.removeAllBakeElements() 
			
			be1 = diffusemap() --instance of the bake element class
			be1.outputSzX = be1.outputSzY = size --set the size of the baked map	
			be1.fileType = outputfile --specify the full file path, name and type:
			be1.fileName = filenameFromPath be1.fileType 
			be1.filterOn = true --enable filtering 
			be1.shadowsOn = false --disable shadows
			be1.lightingOn = false --disable lighting
			be1.enabled = true --enable baking
			
			asteroid.INodeBakeProperties.addBakeElement be1 --add first element
			asteroid.INodeBakeProperties.bakeEnabled = true --enabling baking
			asteroid.INodeBakeProperties.bakeChannel = 1 --channel to bake
			asteroid.INodeBakeProperties.nDilations = 1 --expand the texture a bit

			--Call the renderer to bake both elements:   
			render rendertype:#bakeSelected vfb:off progressBar:true outputSize:[size,size]
			
			asteroid.material = currentMaterialLibrary[viewport_material_id]
		)
	)
	
	,	
	
	/**
	 * Create an asteroid materials
	 */
	fn createMaterials = 
	(
		print "createMaterials"
		
		if color_material_id == undefined then (
			/** Create Global material */
			vertexcolormap = VertexColor()
			colormat = standardMaterial diffusemap: vertexcolormap
			append currentMaterialLibrary colormat
			color_material_id = findItem currentMaterialLibrary colormat
			setUserProp asteroid "color" color_material_id
		)
		
		if ogre_material_id == undefined then (
			/** Create Ogre material */
			ogremat = OgreMax_Material ()	
			ogremat.Techniques[1] = OgreMax_Technique ()
			ogremat.Techniques[1].Passes[1] = OgreMax_Pass()
			
			/*ogremat.Techniques[1].Passes[1] .PixelShader = TERRAINSHADER
			ogremat.Techniques[1].Passes[1] .TextureUnits [1] = OgreMax_Texture_Unit()
			ogremat.Techniques[1].Passes[1] .TextureUnits [1].Bitmap = openBitMap APLHA1
			ogremat.Techniques[1].Passes[1] .TextureUnits [2] = OgreMax_Texture_Unit()
			ogremat.Techniques[1].Passes[1] .TextureUnits [2].Bitmap = openBitMap LAYER1
			ogremat.Techniques[1].Passes[1] .TextureUnits [3] = OgreMax_Texture_Unit()
			ogremat.Techniques[1].Passes[1] .TextureUnits [3].Bitmap = openBitMap LAYER2
			ogremat.Techniques[1].Passes[1] .TextureUnits [4] = OgreMax_Texture_Unit()
			ogremat.Techniques[1].Passes[1] .TextureUnits [4].Bitmap = openBitMap LAYER3

			ogremat.Techniques[1].Passes[1] .TextureUnits [5] = OgreMax_Texture_Unit()
			ogremat.Techniques[1].Passes[1] .TextureUnits [5].Bitmap = openBitMap APLHA2
			ogremat.Techniques[1].Passes[1] .TextureUnits [6] = OgreMax_Texture_Unit()
			ogremat.Techniques[1].Passes[1] .TextureUnits [6].Bitmap = openBitMap LAYER4
			ogremat.Techniques[1].Passes[1] .TextureUnits [7] = OgreMax_Texture_Unit()
			ogremat.Techniques[1].Passes[1] .TextureUnits [7].Bitmap = openBitMap LAYER5
			ogremat.Techniques[1].Passes[1] .TextureUnits [8] = OgreMax_Texture_Unit()
			ogremat.Techniques[1].Passes[1] .TextureUnits [8].Bitmap = openBitMap LAYER6	*/
			
			
			
			
			append currentMaterialLibrary ogremat
			ogre_material_id = findItem currentMaterialLibrary ogremat
		
			setUserProp asteroid "ogre" ogre_material_id
		)
		
		if viewport_material_id == undefined then (
			/** Create DirectX material (viewport) */
			effectfile = terrain_layer1_shader
			if vertexpaintlayers == 2 then
				effectfile = terrain_layer2_shader
			
			dxmat = DxMaterial effectfile:effectfile
			append currentMaterialLibrary dxmat
			viewport_material_id = findItem currentMaterialLibrary dxmat
			setUserProp asteroid "viewport" viewport_material_id
		)		
	)
	
	,
		
	/** 
	 * Initialise the Asteroid info struct 
	 * @param obj, the asteroid object
	 */
	fn create obj = 
	(
		print "create"
		
		asteroid = obj
		
		/* check if one or two vertex paint layers */
		for i = 1 to obj.modifiers.count do (
			if obj.modifiers[i].name == "VertexPaint"  then (	
				vertexpaintlayers += 1
				vertexpaintidices[vertexpaintlayers] = i
			)
		)
		
		/** Read saved properties */
		color_material_id = getUserProp obj "color"
		ogre_material_id =  getUserProp obj "ogre"
		viewport_material_id = getUserProp  obj "viewport"		
		
		/** Crete if nessessary **/
		createMaterials()
	)
	
	,
	
	fn getDxMaterial = 
	(
		if viewport_material_id == undefined then (
			return undefined			
		)
		else (
			return currentMaterialLibrary[viewport_material_id]
		)
	)
	
	,
	
	fn getOgreMaterial = 
	(
		if ogre_material_id == undefined then (
			return undefined
		)
		else (
			return currentMaterialLibrary[ogre_material_id]
		)
	)
	
	,
	
	/** Set current material as color material */
	fn showColor = (
		if color_material_id == undefined then (
			messageBox "No color material found! Use create firts" title:"Error"			
		)
		else (
			asteroid.material = currentMaterialLibrary[color_material_id]
		)
	)
	
	,
	
	/** Set current material as viewport material */
	fn showViewport = (
		if viewport_material_id == undefined then (
			messageBox "No viewport material found! Use create firts" title:"Error"			
		)
		else (
			asteroid.material = currentMaterialLibrary[viewport_material_id]
		)
	)
	
	,
	
	/** Set current material as ogre material */
	fn showOgre = (
		if ogre_material_id == undefined then (
			messageBox "No ogre material found! Use create firts" title:"Error"			
		)
		else (
			asteroid.material = currentMaterialLibrary[ogre_material_id]
		)
	)
	
	,
	
	/** Recreate the alpha maps **/
	fn updateAsteroid size = 
	(		
		print "updateAsteroid"
		
		if color_material_id == undefined or viewport_material_id == undefined then (
			messageBox "No color material or viewport material found! Use create firts" title:"Error"			
		)
		else (		
			
			index = -1
			
			for i = 1 to vertexpaintlayers do (	
				/** current filename **/
				filename =  (getDir #image+"\\" + asteroid.name + (i as string) + "_alpha.png") 
				
				/** disable all but the current vertex color layer */
				for j = 1 to vertexpaintlayers do (
					index = vertexpaintidices[j]
					asteroid.modifiers[index].enabled = false
				)
				
				index = vertexpaintidices[i]
				asteroid.modifiers[index].enabled = true		

				/** create the alpha map **/
				createAlphaMap size filename
			)
			
			/** reenable all vertex color layer */
			for j = 1 to vertexpaintlayers do (
				index = vertexpaintidices[j]
				asteroid.modifiers[index].enabled = true
			)
		)
	)

)

fn checkAsteroid =
(
	sel = getCurrentSelection()
	
	/* Check if one object selected */
	if  sel.count == 0 then (
		messageBox "No object selected, select ONE object" title:"Error"
		return false
	)
	else 
	(
		if sel.count != 1 then (
			messageBox "To manny objects selected, select ONE object" title:"Error"
			return false
		)
		else (
	
			/* save the object in obj */
			obj = sel[1]
			
			vertexpaintlayers = 0
			vertexpaintidices = #(0,0)
			
			/* check if one or two vertex paint layers */
			for i = 1 to obj.modifiers.count do (
				if obj.modifiers[i].name == "VertexPaint"  then (
					vertexpaintlayers += 1
					vertexpaintidices[vertexpaintlayers] = i
				)
			)
	
			if vertexpaintlayers == 0 OR vertexpaintlayers > 2 then(
				messageBox "The selected object has no or to many vertex paint modifiers, it should have at least one, maximum two of these modifiers" title:"Error"
				return false
			)
			else (
				return true
			)
		)
	)			
)

rollout Teleport "Teleport" width:192 height:296
(
	groupBox grp4 "Teleport" pos:[8,8] width:176 height:64
)

rollout AsteroidTool "Asteroid Tool" width:184 height:464
(	
	GroupBox grp2 "Settings" pos:[8,8] width:168 height:200
	edittext size "512" pos:[25,40] width:136 height:16 text:"512"
	GroupBox Actions "GroupBox" pos:[8,216] width:168 height:136
	button update_asteroid "Update" pos:[16,240] width:72 height:21
	button cpyogre "Copy Ogre" pos:[16,272] width:72 height:24
	spinner OgreMat "" pos:[96,272] width:72 height:16 range:[1,24,1] type:#integer
	button cpydx "Copy DX" pos:[16,312] width:72 height:24
	spinner dxmat "" pos:[96,312] width:72 height:16 range:[1,24,1] type:#integer
	GroupBox grp3 "Visual" pos:[8,360] width:168 height:80
	button color_asteroid "Show Color" pos:[24,376] width:64 height:24
	button showOgre "Show Ogre" pos:[96,376] width:64 height:24
	button showDX "Show DX" pos:[96,408] width:64 height:24
		
	mapButton layer1 "Layer1" pos:[16,72] width:72 height:32	
	mapButton layer2 "Layer2" pos:[96,72] width:72 height:32
	mapButton layer3 "Layer3" pos:[16,112] width:72 height:32
	mapButton layer4 "Layer4" pos:[96,112] width:72 height:32
	mapButton layer5 "Layer5" pos:[16,152] width:72 height:32	
	mapButton layer6 "Layer6" pos:[96,152] width:72 height:32
	
	on update_asteroid pressed do
	(	
		sel = getCurrentSelection()
		if sel.count != 1 then (
			messageBox "Select one object" title:"Error"
			return false
		)
		
		sizenr = size.text as number
		if sizenr != 128 and sizenr != 256 and  sizenr != 512 and sizenr != 1024 and sizenr != 2048 then (
			messageBox "Size should be 128, 256, 512, 1024 or 2048" title:"Error"
			return false
		) 
		
		asteroid = AsteroidInfo()
		asteroid.create (sel[1])			
		asteroid.updateAsteroid (sizenr)
	)
	
	on cpyogre pressed do
	(
		sel = getCurrentSelection()		
		if sel.count != 1 then (
			messageBox "Select one object" title:"Error"	
			return false
		)
		
		asteroid = AsteroidInfo()
		asteroid.create (sel[1])	
		
		mat = asteroid.getOgreMaterial()
		if mat != undefined then (
			setMeditMaterial OgreMat.value mat
		)
		else (
			messageBox "No material found, use create firts!" title:"Error"
		)
		
	)
	
	on cpydx pressed do
	(
		sel = getCurrentSelection()	
		if sel.count != 1 then (
			messageBox "Select one object" title:"Error"	
			return false
		)
		
		asteroid = AsteroidInfo()
		asteroid.create (sel[1])	
		
		mat = asteroid.getDxMaterial()
		if mat != undefined then (
			setMeditMaterial DXMat.value mat
		)
		else (
			messageBox "No material found, use create firts!" title:"Error"
		)
	)
	on color_asteroid pressed do
	(
		sel = getCurrentSelection()		
		if sel.count != 1 then (
			messageBox "Select one object" title:"Error"	
			return false
		)
		
		asteroid = AsteroidInfo()
		asteroid.create (sel[1])		
		asteroid.showColor()
	)
	on showOgre pressed do
	(
		sel = getCurrentSelection()		
		if sel.count != 1 then (
			messageBox "Select one object" title:"Error"	
			return false
		)		
		
		asteroid = AsteroidInfo()
		asteroid.create (sel[1])	
		asteroid.showOgre()
	)
	on showDX pressed do
	(
		sel = getCurrentSelection()		
		if sel.count != 1 then (
			messageBox "Select one object" title:"Error"	
			return false
		)
		
		asteroid = AsteroidInfo()
		asteroid.create (sel[1])	
		asteroid.showViewport()
	)
	on layer1 picked texmap do
	(
		terrain_layers[1] = texmap.fileName
	)
	on layer2 picked texmap do
	(
		terrain_layers[2] = texmap.fileName
	)
	on layer3 picked texmap do
	(
		terrain_layers[3] = texmap.fileName
	)
	on layer4 picked texmap do
	(
		terrain_layers[4] = texmap.fileName
	)
	on layer5 picked texmap do
	(
		terrain_layers[5] = texmap.fileName
	)
	on layer6 picked texmap do
	(
		terrain_layers[6] = texmap.fileName
	)
)

rof=newrolloutfloater "Exporter Utilities" 200 500
addrollout AsteroidTool rof
addrollout Teleport rof


