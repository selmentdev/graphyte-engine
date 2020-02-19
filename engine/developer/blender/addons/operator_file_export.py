import bpy

def dump(obj, level=0):
   for attr in dir(obj):
       if hasattr( obj, "attr" ):
           print( "obj.%s = %s" % (attr, getattr(obj, attr)))
       else:
           print( attr )
           
def write_mesh(f, obj):
    
    # dump(obj.data)
    mesh = obj.data

    if len(mesh.uv_layers) > 0:
        mesh.calc_tangents()
    
    f.write('  - mesh vertices: %d\n' % len(mesh.vertices))

    for index, vertex in enumerate(mesh.vertices):
        f.write('    - vertex [%d]\n' % (index))
        f.write('      - position:    %s\n' % (vertex.co))
        f.write('      - normal:      %s\n' % (vertex.normal))
        f.write('      - groups:      %d\n' % (len(vertex.groups)))
        for group in vertex.groups:
            f.write('        - %s\n' % (group))
    
    
    f.write('  - mesh faces: %d\n' % len(mesh.polygons))
    
    for index, face in enumerate(mesh.polygons):
        f.write('    - face [%d]\n' % (index))
        f.write('      - use-smooth:      %r\n' % (face.use_smooth))
        f.write('      - material-index:  %d\n' % (face.material_index))
        f.write('      - vertices:        %d\n' % (len(face.vertices)))
        f.write('      - center:          %s\n' % (face.center))
        f.write('      - normal:          %s\n' % (face.normal))
        f.write('      - vertices:        %d\n' % (len(face.vertices)))
        for vert_idx, vert in enumerate(face.vertices):
            f.write('        - [%d]:           %s\n' % (vert_idx, vert))
        f.write('      - loop-indices:    %d\n' % (len(face.loop_indices)))
        for loop_idx, loop in enumerate(face.loop_indices):
            f.write('        - [%d]:           %s\n' % (loop_idx, loop))

    f.write('  - mesh loops: %d\n' % len(mesh.loops))
    
    for index, loop in enumerate(mesh.loops):
        f.write('    - loop [%d]\n' % (index))
        f.write('      - normal:          %s\n' % (loop.normal))
        f.write('      - tangent:         %s\n' % (loop.tangent))
        bitangent = loop.bitangent_sign * loop.normal.cross(loop.tangent)
        f.write('      - bitangent:       %s\n' % (bitangent))
        f.write('      - bitangent-sign:  %s\n' % (loop.bitangent_sign))
        
    f.write('  - mesh uv layers: %d\n' % (len(mesh.uv_layers)))
    
    for index, layer in enumerate(mesh.uv_layers):
        f.write('    - uvlayer [%d]\n' % (index))
        for uv_index, uv in enumerate(layer.data):
            f.write('      - [%d] %s\n' % (uv_index, uv.uv))
    


def write_some_data(context, filepath, use_some_setting):
    f = open(filepath, 'w', encoding='utf-8')

    #obj = bpy.data.objects["Cube"]  # particular object by name
    for obj in bpy.context.scene.objects:
        objType = getattr(obj, 'type', '')
        if objType in ['MESH']:
            f.write('- name: %s\n' % getattr(obj, 'name'))
            f.write('- matrix: %s\n' % obj.matrix_local.transposed())
            f.write('- children: %d\n' % len(obj.children))
            for child in obj.children:
                f.write('-- child: %s\n' % child)
            write_mesh(f, obj)
        
    #obj = bpy.context.scene.objects.active # active object
    f.close()
    print('finish!')
    return {'FINISHED'}


# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator


class ExportSomeData(Operator, ExportHelper):
    """This appears in the tooltip of the operator and in the generated docs"""
    bl_idname = "export_test.some_data xxx"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "Export Some Data xxxx"

    # ExportHelper mixin class uses this
    filename_ext = ".txt"

    filter_glob = StringProperty(
            default="*.txt",
            options={'HIDDEN'},
            maxlen=255,  # Max internal buffer length, longer would be clamped.
            )

    use_mesh_modifiers = BoolProperty(
        name="Apply Modifiers",
        description="Apply modifiers to mesh objects",
        default=True,
    )
    
    object_types = EnumProperty(
        name = 'Object Types',
        options = {'ENUM_FLAG'},
        items = (
            ('EMPTY', "Empty", ""),
            ('CAMERA', "Camera", ""),
            ('LAMP', "Lamp", ""),
            ('ARMATURE', "Armature", "WARNING: not supported in dupli/group instances"),
            ('MESH', "Mesh", ""),
            ('OTHER', "Other", "Other geometry types, like curve, metaball, etc. (converted to meshes)"),
        ),
        description = "Which kind of object to export",
        default = {'EMPTY', 'CAMERA', 'LAMP', 'ARMATURE', 'MESH', 'OTHER'},
    )
    
    use_export_normals = BoolProperty(
        name = 'Export Normals',
        description = 'Export Normals',
        default = True
    )
    
    use_export_tangents = BoolProperty(
        name = 'Export Tangents',
        description = 'Export Tangents',
        default = False
    )
    
    use_export_uvs = EnumProperty(
        name = 'Export UVs',
        options = {'ENUM_FLAG'},
        items = (
            ('UV1', 'UV1', ''),
            ('UV2', 'UV2', ''),
            ('UV3', 'UV3', ''),
            ('UV4', 'UV4', ''),
            ('UV5', 'UV5', ''),
            ('UV6', 'UV6', ''),
            ('UV7', 'UV7', ''),
            ('UV8', 'UV8', ''),
        ),
        description = 'Which UV layers to export',
        default = {'UV1'},
    )
    
    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.
    use_setting = BoolProperty(
            name="Example Boolean",
            description="Example Tooltip",
            default=True,
            )

    type = EnumProperty(
            name="Example Enum",
            description="Choose between two items",
            items=(('OPT_A', "First Option", "Description one"),
                   ('OPT_B', "Second Option", "Description two")),
            default='OPT_A',
            )

    def execute(self, context):
        return write_some_data(context, self.filepath, self.use_setting)


# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ExportSomeData.bl_idname, text="Text Export Operator")


def register():
    bpy.utils.register_class(ExportSomeData)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportSomeData)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()

    # test call
    bpy.ops.export_test.some_data('INVOKE_DEFAULT')
