macroscript TrackScript category: "Hovercraft Univer Tools"
(
	local floater
	rollout TrackRollout "Rollout" width:216 height:96
	(
			fn shapeFilter obj = iskindof obj Shape
				
			pickbutton btnPickShape "..." pos:[176,16] width:32 height:16 filter:shapeFilter
			button btnOk "OK" pos:[152,72] width:56 height:16
			edittext txtShape "Shape" pos:[16,16] with:152 height:16 enabled:false
			spinner spnSubdivisions "Subdivisions" pos:[24,40] width:184 height:16 range:[0,100,10] type:#integer
			button btnCancel "Cancel" pos[96,72] width:48 height:16
		
			on btnOk pressed do
			(
				nrOfElements = spnSubdivisions.value -1
				s = getNodeByName textShape.text
				for i = 0 to nrOfElements do
				(
					p = lengthInterp s 1 (1.0 * i / nrOfElements)
					b = box pos:p width: 1 length:1 height:10
				)
				closeRolloutFloater floater
			)
			
			on btnPickShape picked obj do 
			(
					txtShape.text = obj.name
			)
			
			on btnCancel pressed do 
			(
				closeRolloutFloater floater
			)
	)
	
	on Execute do 
	(
			floater  = NewRolloutFloater "Track Creator" 500 200
			addRollout TrackRollout floater
	)
)