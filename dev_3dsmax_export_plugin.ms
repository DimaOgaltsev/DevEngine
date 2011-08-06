max modify mode
rollout expmesh "Export Mesh"
(	
  	editText edt_path "Path" pos:[10,10] width:300
    button btn_browse "Browse" pos:[320,8] width:50   
    button btn_exp "Export" pos:[320,35] width:50 
    checkBox chk_i "Indexes" pos:[10,35] checked:true
    checkBox chk_t "TexCoord" pos:[70,35] checked:true
    checkBox chk_n "Normals" pos:[140,35] checked:true

	on expmesh open do
      (
        edt_path.text = (GetDir #Export) + "\\model.dfm"
      )
	on btn_browse pressed do
      (
        s = GetSaveFileName types:"DevFileModel (*.dfm)|*.dfm|All files (*.*)|*.*"
		if (s != undefined) do
          edt_path.text = s
      )
	on btn_exp pressed do
      (
  		local bI=0
		local bT=0
       	local bN=0
		
		if (chk_i.checked == true) then bI=1
        if (chk_n.checked == true) then bN=1
        if (chk_t.checked == true) then bT=1
		
		if edt_path.text != undefined do
        (
 			file = fopen edt_path.text "wb"
			
			if (bI == 1) then
				writeLong file 0xE1A2B400
			else
				writeLong file 0xF1A2B400
			
			mcount = 0
			for obj in Objects do
				if (classOf obj != BoneGeometry) and (classOf obj != Biped_Object) and (canConvertTo obj TriMeshGeometry) then
					mcount += 1

			writeLong file mcount
		
			vt = 1
			if (bT == 1) then
			  vt += 2
			if (bN == 1) then
			  vt += 4
			  
			writeLong file vt
			
			for obj in Objects do
				if (classOf obj != BoneGeometry) and (classOf obj != Biped_Object) and (canConvertTo obj TriMeshGeometry) then
				(
					mesh = copy obj
					convertToMesh mesh
					
					writeLong file mesh.numVerts
					writeLong file mesh.numFaces
					
					if (bI == 1) then
					(
						for i = 1 to mesh.numVerts do
						(
							v = (getVert mesh i)
							writeFloat file v.x				
							writeFloat file v.z
							writeFloat file v.y
							
							if (bN == 1) then
							(  
								n = (getNormal mesh i)
	                       		writeFloat file n.x
		                        writeFloat file n.z                    
		                        writeFloat file n.y  
							)
						
							if (bT == 1) then
							(
								if (mesh.numTVerts > 0) then
								(
									t = (getTVert mesh i)
									writeFloat file t.x	
									writeFloat file (1-t.y)								
								)
								else 
								(
									writeFloat file 0	
									writeFloat file 0	
								)
							)						
						)
						
						for i = 1 to mesh.numFaces do
						(
							f = (getFace mesh i)
							writeLong file (f.x-1)
							writeLong file (f.z-1)
							writeLong file (f.y-1)
						)
					) 
					else
					(
						for i = 1 to mesh.numFaces do
						(
							f = (getFace mesh i)
							if (mesh.numTVerts > 0) then
								tvf = (getTVFace mesh i)
							n = getFaceNormal mesh i
	
							v = (getVert mesh f.x)
							writeFloat file v.x				
							writeFloat file v.z
							writeFloat file v.y
							  
							if (bN == 1) then
							(  
	                       		writeFloat file n.x
		                        writeFloat file n.z                    
		                        writeFloat file n.y  
							)
							
							if (bT == 1) then
							(
								if (mesh.numTVerts > 0) then
								(
									t = (getTVert mesh tvf.x)
									writeFloat file t.x	
									writeFloat file (1-t.y)								
								)
								else 
								(
									writeFloat file 0
									writeFloat file 0	
								)
							)
							
							v = (getvert mesh f.z)
							writeFloat file v.x				
							writeFloat file v.z
							writeFloat file v.y
	  
	  						if (bN == 1) then
							( 
	                       		writeFloat file n.x
		                        writeFloat file n.z                    
		                        writeFloat file n.y
							)
			
							if (bT == 1) then
							(
								if (mesh.numTVerts > 0) then
								(
									t = (getTVert mesh tvf.z)
									writeFloat file t.x	
									writeFloat file (1-t.y)								
								)
								else 
								(
									writeFloat file 0	
									writeFloat file 0	
								)
							)
							
							v = (getvert mesh f.y)
 							writeFloat file v.x				
 							writeFloat file v.z
 							writeFloat file v.y
   	
   							if (bN == 1) then
							( 
	                       		writeFloat file n.x
		                        writeFloat file n.z                    
		                        writeFloat file n.y
							)
							
							if (bT == 1) then
							(
								if (mesh.numTVerts > 0) then
								(
									t = (getTVert mesh tvf.y)
									writeFloat file t.x	
									writeFloat file (1-t.y)									
								)
								else 
								(
									writeFloat file 0	
									writeFloat file 0	
								)
							)
						)
					)
			
				delete mesh
				)
			fclose file
			)
        )
)

m_roll = newrolloutfloater "Dev File Exporter" 400 93

addrollout expmesh m_roll