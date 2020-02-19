import os
import sys
import logging
import bpy

from . import export

bl_info = {
    "name":         "Graphyte Mesh Exporter",
    "author":       "Karol Grzybowski",
    "version":      (1, 0, 0),
    "blender":      (2, 7, 5),
    "location":     "File > Export...",
    "description":  "Export to Graphyte Mesh format",
    "wiki_url":     "",
    "tracker_url":  "",
    "category":     "Import-Export"
}

"""
@brief  This class implements global addon preferences for Graphyte Engine tools.
"""
class GraphyteMeshExporter(bpy.types.AddonPreferences):
    bl_idname = __name__

    ENABLE_FANCY_THINGS = bpy.props.BoolProperty(
        name = 'Enable Fancy Things',
        default = False
    )
    
    def draw(self, context):
        layout = self.layout
        layout.prop(self, "ENABLE_FANCY_THINGS")
        
def register():
    logging.info("Starting Graphyte Mesh Exporter %s", bl_info["version"])
    
    bpy.utils.register_class(GraphyteMeshExporter)

    print('register addon')
    export.register()
    
def unregister():
    logging.info("Stopping Graphyte Mesh Exporter")
    
    export.unregister()
    
    bpy.utils.unregister_class(GraphyteMeshExporter)
    
if __name__ == "__main__":
    register()