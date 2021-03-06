# To execute in the blender console
# filename = "/home/dennisyu/Documents/WMSN/TopologyGen/cameraBigTopology.py"
# exec(compile(open(filename).read(), filename, 'exec'))

import bpy
import random
import math

###City settings
#city size 2000m^2, Seed = 4
#Create terrain = 1, Create meterials (sampling size) = 1, (texture size) = 2000, maximum height = 300, water level = 0, random options = 0
#Street texture size = 5000, slope limit = 5, Manhattan
#high poly models = 5, Total meterials = 15, texture size = 5000

# way of remove object, we need to select the objects first
# gather list of items of interest.
bpy.ops.object.select_all(action="DESELECT")
# remove all objects except the city.
removeList = [item.name for item in bpy.data.objects if item.type == "CAMERA" or item.type == "LAMP"]
for obj in removeList:
	bpy.data.objects[obj].select = True
bpy.ops.object.delete()

#move all the objects
bpy.ops.object.select_all(action="SELECT")
cityObjectList = [item.name for item in bpy.data.objects if item.select == True]
for obj in cityObjectList:
	bpy.data.objects[obj].location = [-10.0, -10.0, -3.0]

#bpy.ops.group.create(name="myCity")
#bpy.ops.object.group_link(group="myCity")
#myCity.location = [0.0, 0.0, 0.0]
#bpy.ops.object.location = [0.0, 0.0, 0.0]

# add light
scene = bpy.context.scene
lamp_data = bpy.data.lamps.new(name="sun1", type='SUN')
lamp_data.energy = 1.0
lamp_data.sky.use_sky = True
lamp_data.sky.use_atmosphere = True
lamp_object = bpy.data.objects.new(name="sun1", object_data=lamp_data)
scene.objects.link(lamp_object)
lamp_object.location = (0.0, 0.0, 10.0)
lamp_object.select = True

lamp_data = bpy.data.lamps.new(name="sun2", type='HEMI')
lamp_data.energy = 1.0
lamp_object = bpy.data.objects.new(name="sun2", object_data=lamp_data)
scene.objects.link(lamp_object)
lamp_object.location = (0.0, 0.0, 10.0)
lamp_object.select = True

scene.objects.active = lamp_object

#add camera (fix position)

#Group 1
cameraPos = (-5.8, -7.3, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*90.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-5.75, -7.3, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*100.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-2.0, -7.3, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*90.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-2.05, -7.3, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*95.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-1.2, -6.9, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*15.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-1.23, -6.9, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*15.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (0.1, -7.4, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*90.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (0.15, -7.4, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*95.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-8.0, -7.8, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*270.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-8.03, -7.8, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*270.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-6.1, -8.42, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*90.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-6.1, -8.4, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*90.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-2.13, -9.1, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*15.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-2.15, -9.1, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*15.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-0.05, -0.9, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*10.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.1, -0.9, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*10.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-6.83, -1.0, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*15.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-6.85, -1.0, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*20.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-4.2, -2.67, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*320.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-4.2, -2.70, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*320.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-5.0, -5.0, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*320.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-6.2, -2.70, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*20.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-3.4, -3.6, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*35.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-7.1, -4.9, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*150.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-2.2, -3.70, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*220.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

#Group 2
cameraPos = (-7.43, 3.05, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*30.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-7.43, 3.1, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*33.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-8.5, 5.08, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*90.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-8.5, 5.1, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*90.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-4.46, 9.0, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*180.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-4.5, 9.0, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*185.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-6.2, 2.5, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*190.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-6.25, 2.5, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*195.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-0.5, 6.08, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*275.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.5, 6.1, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*270.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-0.5, 6.74, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*90.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.5, 6.7, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*95.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-0.5, 3.94, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*60.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-0.5, 3.9, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*65.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-2.94, 0.91, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*180.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-2.9, 0.91, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*185.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-3.8, 2.81, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*275.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-3.8, 2.85, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*280.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-9.549, 9.0, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*180.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-9.5, 9.0, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*185.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (-5.5, 5.0, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*18.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-2.4, 1.1, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*85.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-3.5, 6.9, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*155.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-1.5, 0.8, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*105.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (-7.5, 3.0, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*25.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

#Group 3
cameraPos = (3.0, 0.78, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*100.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (3.0, 0.7, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*100.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (2.0, 1.06, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*175.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (2.0, 1.1, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*170.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (7.5, 0.85, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*255.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (7.5, 0.8, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*250.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (7.5, 2.3, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*330.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (7.5, 2.35, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*325.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (9.5, 4.27, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*260.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (9.5, 4.3, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*265.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (8.08, 5.16, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*180.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (8.1, 5.16, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*185.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (2.0, 5.08, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*340.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (2.0, 5.1, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*345.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (2.13, 6.65, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*270.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (2.1, 6.6, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*275.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (3.5, 7.2, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*200.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (3.5, 7.25, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*205.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (7.0, 8.95, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*225.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (7.0, 9.0, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*220.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (7.3, 2.0, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*20.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (6.5, 8.0, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*120.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (2.0, 7.2, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*50.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (4.3, 1.6, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*80.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (6.4, 4.6, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*170.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

#Group 4
cameraPos = (2.56, -2.17, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*0.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (2.56, -2.2, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*5.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (4.15, -2.5, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*155.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (4.2, -2.5, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*150.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (5.45, -2.0, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*175.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (5.4, -2.0, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*170.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (7.4, -2.11, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*270.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (7.41, -2.1, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*275.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (9.69, -4.0, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*190.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (9.69, -4.05, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*195.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (7.27, -5.46, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*8.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (7.3, -5.46, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*10.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (3.55, -5.8, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*350.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (3.5, -5.8, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*352.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (3.46, -8.16, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*275.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (3.4, -8.16, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*270.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (5.03, -8.85, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*185.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (5.0, -8.85, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*180.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (7.91, -8.83, 0.1)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*5.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (7.9, -8.8, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*8.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);

cameraPos = (2.6, -1.2, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*8.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (3.4, -4.7, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*58.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (7.9, -7.8, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*108.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (0.4, -5.4, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*78.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);
cameraPos = (4.8, -6.1, 0.11)
cameraRotation = (math.pi*90.0/180, math.pi*0.0/180, -math.pi*98.0/180)
bpy.ops.object.camera_add(view_align=False, enter_editmode=False, location=cameraPos, rotation=cameraRotation);


bpy.data.scenes["Scene"].render.resolution_x = 1280*2;
bpy.data.scenes["Scene"].render.resolution_y = 720*2;
# object has a attribute named type which can query the type
# print(str(object.type))
for object in bpy.data.objects:
    print(object.name+" is at location " + str(object.location))

# to setup the camera field of view(FoV)
#bpy.data.scenes["Scene"].camera.data.angle_x
#bpy.data.scenes["Scene"].camera.data.angle_y
	
	
print('\nPrint Scenes...'); 
sceneKey = bpy.data.scenes.keys()[0]; 
print('Using Scene['  + sceneKey + ']');
c=0;
logFileName="//home/dennisyu/Documents/WMSN/TestSequences/myBigCity_png/log.txt"
logFile=open(logFileName,"w+")
for obj in bpy.data.objects: 
# Find cameras that match cameraNames 
    if ( obj.type =='CAMERA'): 
        print("Rendering scene["+sceneKey+"] with Camera["+obj.name+"]")
        logFile.write("Rendering scene["+sceneKey+"] with Camera["+obj.name+"]\n") 
        location = obj.location
        rotation = obj.rotation_euler 
        logFile.write("Pos "+str(location.x)+" "+str(location.y)+" "+str(location.z)+" Dir "+str(rotation.x)+" "+str(rotation.y)+" "+str(rotation.z)+"\n")
        # Set Scenes camera and output filename 
        bpy.data.scenes[sceneKey].camera = obj 

        # Render Scene and store the scene 
        bpy.ops.render.render( write_still=True ); 
        RR = "Render Result";
        bpy.data.images[RR].save_render("/home/dennisyu/Documents/WMSN/TestSequences/myBigCity_png/camera_"+str(c)+".png");
        c = c + 1; 

logFile.close()
