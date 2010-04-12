fn createAsteroid = 
(
	size = 1024
	sel = getCurrentSelection()
	obj = sel[1]	
	
	vertexpaintidices = #(0,0)
	vertexpaintlayers = 0
	
	/* check if one or two vertex paint layers */
	for i = 1 to obj.modifiers.count do (
		if obj.modifiers[i].name == "VertexPaint"  then (			
			vertexpaintlayers += 1
			vertexpaintidices[vertexpaintlayers] = i
		)
	)	
	
	/* keep copy off material */
	mat = obj.material
	colormap = Vertex_Color ()
	obj.material = standard diffusemap:colormap	
	
	for i = 1 to vertexpaintlayers do (
		
		/** disable all but the current vertex color layer */
		for j = 1 to vertexpaintlayers do (
			obj.modifiers[j].enabled = false
		)
		obj.modifiers[i].enabled = true		
				
		/* clean all previous */
		obj.iNodeBakeProperties.removeAllBakeElements() 
		
		be1 = diffusemap() --instance of the bake element class
		be1.outputSzX = be1.outputSzY = size --set the size of the baked map
		--specify the full file path, name and type:
		
		filename = (getDir #image+"\\" + obj.name + (i as string) + "_alpha.png") 
		be1.fileType = filename
		be1.fileName = filenameFromPath be1.fileType 
		be1.filterOn = true --enable filtering 
		be1.shadowsOn = false --disable shadows
		be1.lightingOn = false --disable lighting
		be1.enabled = true --enable baking
		
		obj.INodeBakeProperties.addBakeElement be1 --add first element
		obj.INodeBakeProperties.bakeEnabled = true --enabling baking
		obj.INodeBakeProperties.bakeChannel = 1 --channel to bake
		obj.INodeBakeProperties.nDilations = 1 --expand the texture a bit

		--Call the renderer to bake both elements:   
		render rendertype:#bakeSelected vfb:off progressBar:true outputSize:[size,size]
	)
	
	/** reenable all vertex color layer */
	for j = 1 to vertexpaintlayers do (
		obj.modifiers[j].enabled = true
	)
	
	/** restore material **/
	obj.material = mat
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

rollout HovermaxWorldExporter "World Exporter" width:184 height:320
(
	GroupBox grp1 "Asteroid Tool" pos:[8,8] width:168 height:168
	mapButton la1 "Layer1" pos:[16,32] width:72 height:24
	mapButton la2 "Layer2" pos:[16,64] width:72 height:24
	mapButton la3 "Layer3" pos:[16,96] width:72 height:24
	mapButton la4 "Layer4" pos:[96,32] width:72 height:24
	mapButton la5 "Layer5" pos:[96,64] width:72 height:24
	mapButton la6 "Layer6" pos:[96,96] width:72 height:24
	button create_asteroid "Create" pos:[96,136] width:72 height:24
	button check_asteroid "Check" pos:[16,136] width:72 height:24
	
	on create_asteroid pressed  do
	(
		check = checkAsteroid()
		if check  then (		
			createAsteroid()
		)	
	)
	
	on check_asteroid pressed do
	(
		check = checkAsteroid()
		if check  then (		
			messageBox "Alright the create function will work!" title:"Success"
		)		
	)
)

rof=newrolloutfloater "Exporter Utility" 200 400
addrollout HovermaxWorldExporter rof


