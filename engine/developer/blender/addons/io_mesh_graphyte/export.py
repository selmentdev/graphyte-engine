import bpy

# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator

class ExportSomeData(Operator, ExportHelper):
    """This appears in the tooltip of the operator and in the generated docs"""
    bl_idname = "graphyte_export.model_format"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "Export Graphyte Model Format"

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
        return self.emit_scene(context)

    """
    Emitter interface
    """
    def emit_file_header(self, context):
        self.file.write('%YAML 1.1\n')
        self.file.write('---\n')
        self.file.write('format-version: 1\n')
        self.file.write('meshes:\n')

    def emit_file_footer(self, context):
        self.file.write('...\n')

    def emit_vector2(self, value):
        return '[{0:0.6f}, {1:0.6f}]'.format(value.x, value.y)
    def emit_vector3(self, value):
        return '[{0:0.6f}, {1:0.6f}, {2:0.6f}]'.format(value.x, value.y, value.z)

    def emit_vector4(self, value):
        return '[{0:0.6f}, {1:0.6f}, {2:0.6f}, {3:0.6f}]'.format(value.x, value.y, value.z, value.w)

    def emit_object(self, context, object):

        object.data.calc_normals()

        has_tangents = len(object.data.uv_layers) > 0

        if has_tangents:
            object.data.calc_tangents()

        self.file.write('- name: {0}\n'.format(object.name))
        self.file.write('  index: {0}\n'.format(self.object_mapping.get(object, -1)))
        self.file.write('  parent: {0}\n'.format(self.object_mapping.get(object.parent, -1)))
        self.file.write('  local-transform:\n')
        xform = object.matrix_local.transposed()
        self.file.write('  - {0}\n'.format(self.emit_vector4(xform[0])))
        self.file.write('  - {0}\n'.format(self.emit_vector4(xform[1])))
        self.file.write('  - {0}\n'.format(self.emit_vector4(xform[2])))
        self.file.write('  - {0}\n'.format(self.emit_vector4(xform[3])))

        # Emit per-face material indices
        self.file.write('  faces:\n')
        for face in object.data.polygons:
            self.file.write('  - {{ material: {0}, smooth: {1}, normal: {2} }}\n'.format(
                face.material_index,
                1 if face.use_smooth else 0,
                self.emit_vector3(face.normal)
            ))

        # Emit vertices
        self.file.write('  vertices:\n')
        for vertex in object.data.vertices:
            self.file.write('  - {0}\n'.format(self.emit_vector3(vertex.co)))

        # Emit wedge indices
        self.file.write('  wedge-to-vertex-mapping:\n')
        for face in object.data.polygons:
            print(len(face.loop_indices))
            assert(len(face.loop_indices) == 3)
            self.file.write('  - [{0}, {1}, {2}]\n'.format(face.vertices[0], face.vertices[1], face.vertices[2]))

        # Emit wedge normal
        self.file.write('  wedge-normals:\n')
        for loop in object.data.loops:
            n = loop.normal
            self.file.write('  - {0}\n'.format(self.emit_vector3(n)))

        self.file.write('  wedge-tangent:\n')
        if has_tangents:
            for loop in object.data.loops:
                t = loop.tangent
                self.file.write('  - {0}\n'.format(self.emit_vector3(t)))

        self.file.write('  wedge-bitangent:\n')
        if has_tangents:
            for loop in object.data.loops:
                b = loop.bitangent_sign * loop.normal.cross(loop.tangent)
                s = loop.bitangent_sign
                self.file.write('  - [{0}, {1}]\n'.format(self.emit_vector3(b), s))

        self.file.write('  wedge-texcoords:\n')
        for texcoords in object.data.uv_layers:
            self.file.write('  -\n')
            for coord in texcoords.data:
                self.file.write('    - {0}\n'.format(self.emit_vector2(coord.uv)))

    def emit_scene(self, context):

        self.object_mapping = self.gather_mesh_object_indices(context)

        self.file = open(self.filepath, 'w', encoding = 'utf-8')

        self.emit_file_header(context)

        # Export all objects
        for object in context.scene.objects:
            if getattr(object, 'type', '') in ['MESH']:
                self.emit_object(context, object)

        self.emit_file_footer(context)

        self.file.close()
        return {'FINISHED'}

    def gather_mesh_object_indices(self, context):
        result = {}
        for key, value in enumerate(context.scene.objects):
            result[value] = key

        return result


    def write_mesh(self, f, obj):

        mesh = obj.data



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

    def write_objects(self, context, filepath, use_some_setting):

        f = open(filepath, 'w', encoding='utf-8')

        #obj = bpy.data.objects["Cube"]  # particular object by name
        for obj in bpy.context.scene.objects:
            objType = getattr(obj, 'type', '')
            if objType in ['MESH']:
                f.write('- name: %s\n' % getattr(obj, 'name'))
                f.write('- object index: {0}\n'.format(self.object_mapping.get(obj, -1)))
                f.write('- parent index: {0}\n'.format(self.object_mapping.get(obj.parent, -1)))
                f.write('- matrix: %s\n' % obj.matrix_local.transposed())
                f.write('- children: %d\n' % len(obj.children))
                for child in obj.children:
                    f.write('-- child: %s\n' % child)
                self.write_mesh(f, obj)

        #obj = bpy.context.scene.objects.active # active object
        f.close()
        print('finish!')
        return {'FINISHED'}

# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ExportSomeData.bl_idname, text="Export Graphyte Model")


def register():
    bpy.utils.register_class(ExportSomeData)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportSomeData)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()

    # test call
    bpy.ops.graphyte_export.model_format('INVOKE_DEFAULT')
