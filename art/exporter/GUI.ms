shaderfx = pathConfig.getCurrentProjectFolder()  + "\\shaderfx\\"
terrain_layer1_shader = shaderfx + "terrain1.fx"
terrain_layer2_shader = shaderfx + "terrain2.fx"

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
	
	/**
	 * Create an asteroid materials
	 */
	fn createMaterials = 
	(
		print "createMaterials"
		
		/** Create Global material */
		vertexcolormap = VertexColor()
		colormat = standardMaterial diffusemap: vertexcolormap
		append currentMaterialLibrary colormat
		color_material_id = findItem currentMaterialLibrary colormat
		
		print colormat
		print color_material_id
		
		/** Create Ogre material TODO */
		/*ogremat = material 
		append currentMaterialLibrary ogremat
		ogrematid = findItem currentMaterialLibrary ogremat*/
		ogre_material_id = -1
		
		/** Create DirectX material (viewport) */
		effectfile = terrain_layer1_shader
		if vertexpaintlayers == 2 then
			effectfile = terrain_layer2_shader
		
		dxmat = DxMaterial effectfile:effectfile
		append currentMaterialLibrary dxmat
		viewport_material_id = findItem currentMaterialLibrary dxmat
		
		print dxmat
		print viewport_material_id
		
		/** Save as properties */
		setUserProp asteroid "color" color_material_id
		setUserProp asteroid "viewport" viewport_material_id
		setUserProp asteroid "ogre" ogre_material_id
	)
	
	,
	
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

rollout HovermaxWorldExporter "World Exporter" width:184 height:464
(
	GroupBox grp1 "Asteroid Tool" pos:[8,8] width:168 height:448
	button create_asteroid "Create" pos:[96,144] width:72 height:24
	button check_asteroid "Check" pos:[16,144] width:72 height:24	
	label lbl1 "Viewport" pos:[16,32] width:56 height:24
	label lbl3 "Ogre" pos:[16,64] width:56 height:24
	edittext size "512" pos:[80,104] width:88 height:24 text:"512"
	label lbl4 "Size" pos:[16,104] width:56 height:24	
	edittext view "Viewport" pos:[80,32] width:88 height:24 readOnly:true
	edittext Ogre "Ogre" pos:[80,64] width:88 height:24 readOnly:true
	button update_asteroid "Update" pos:[16,177] width:72 height:21
	button color_asteroid "Show Color" pos:[16,288] width:72 height:24
	button cpyogre "Copy Ogre" pos:[16,208] width:72 height:24
	spinner OgreMat "" pos:[96,208] width:72 height:16 range:[1,24,1] type:#integer
	button cpydx "Copy DX" pos:[16,240] width:72 height:24
	spinner dxmat "" pos:[96,240] width:72 height:16 range:[1,24,1] type:#integer
	button showOgre "Show Ogre" pos:[96,288] width:72 height:24
	button showDX "Show DX" pos:[16,320] width:72 height:24
	
	on create_asteroid pressed do
	(
		sel = getCurrentSelection()		
		asteroid = AsteroidInfo()
		asteroid.create (sel[1])		
		asteroid.createMaterials ()
	)
	on check_asteroid pressed do
	(
		check = checkAsteroid( size.text as number )
		if check  then (		
			messageBox "Alright the create function will work!" title:"Success"
		)		
	)
	on update_asteroid pressed do
	(	
		sel = getCurrentSelection()
		
		asteroid = AsteroidInfo()
		asteroid.create (sel[1])		
		
		sizenr = size.text as number
		
		/** size should be of power 2  128, 256, 512, 1024 or 2048*/
		if sizenr != 128 and sizenr != 256 and  sizenr != 512 and sizenr != 1024 and sizenr != 2048 then (
			messageBox "Size should be 128, 256, 512, 1024 or 2048" title:"Error"
		) else (
			asteroid.updateAsteroid (sizenr)
		)	
		
	)

	on cpyogre pressed do
	(
		sel = getCurrentSelection()		
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
		asteroid = AsteroidInfo()
		asteroid.create (sel[1])	
	
		asteroid.showColor()
	)
	
	on showOgre pressed  do
	(
		sel = getCurrentSelection()		
		asteroid = AsteroidInfo()
		asteroid.create (sel[1])	
	
		asteroid.showOgre()
	)
	
	on showDX pressed  do
	(
		sel = getCurrentSelection()		
		asteroid = AsteroidInfo()
		asteroid.create (sel[1])	
	
		asteroid.showViewport()
	)
)

rof=newrolloutfloater "Exporter Utility" 200 400
addrollout HovermaxWorldExporter rof


