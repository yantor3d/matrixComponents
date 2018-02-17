/**
Copyright (c) 2018 Ryan Porter
*/

/*
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
matrixComponents

Maya plugin with nodes that return individual transform components from a matrix.
*/

#include "matrixToEulerNode.h"
#include "matrixToPositionNode.h"
#include "matrixToQuatNode.h"
#include "matrixToRowsNode.h"
#include "matrixToScaleNode.h"
#include "matrixToShearNode.h"

#include <maya/MFnPlugin.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

const char* AUTHOR               = "Ryan Porter";
const char* VERSION              = "1.0.0";
const char* REQUIRED_API_VERSION = "Any";

MString MatrixToEulerRotation::NODE_NAME = "matrixToEuler";
MString MatrixToPosition::NODE_NAME      = "matrixToPosition";
MString MatrixToQuaternion::NODE_NAME    = "matrixToQuaternion";
MString MatrixToRows::NODE_NAME          = "matrixToRows";
MString MatrixToScale::NODE_NAME         = "matrixToScale";
MString MatrixToShear::NODE_NAME         = "matrixToShear";

MTypeId MatrixToEulerRotation::NODE_ID   = 0x00126b34;
MTypeId MatrixToPosition::NODE_ID        = 0x00126b35;
MTypeId MatrixToQuaternion::NODE_ID      = 0x00126b36;
MTypeId MatrixToRows::NODE_ID            = 0x00126b37;
MTypeId MatrixToScale::NODE_ID           = 0x00126b38;
MTypeId MatrixToShear::NODE_ID           = 0x00126b39;

#define REGISTER_NODE(NODE)              \
    status = fnPlugin.registerNode(      \
        NODE::NODE_NAME,                 \
        NODE::NODE_ID,                   \
        NODE::creator,                   \
        NODE::initialize                 \
    );                                   \
    CHECK_MSTATUS_AND_RETURN_IT(status); \


#define DEREGISTER_NODE(NODE)            \
    status = fnPlugin.deregisterNode(    \
        NODE::NODE_ID                    \
    );                                   \
    CHECK_MSTATUS_AND_RETURN_IT(status); \


MStatus initializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin fnPlugin(obj, AUTHOR, VERSION, REQUIRED_API_VERSION);

    REGISTER_NODE(MatrixToEulerRotation)
    REGISTER_NODE(MatrixToPosition)
    REGISTER_NODE(MatrixToQuaternion)
    REGISTER_NODE(MatrixToRows)
    REGISTER_NODE(MatrixToScale)
    REGISTER_NODE(MatrixToShear)

    return status;
}


MStatus uninitializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin fnPlugin(obj, AUTHOR, VERSION, REQUIRED_API_VERSION);
    
    DEREGISTER_NODE(MatrixToEulerRotation)
    DEREGISTER_NODE(MatrixToPosition)
    DEREGISTER_NODE(MatrixToQuaternion)
    DEREGISTER_NODE(MatrixToRows)
    DEREGISTER_NODE(MatrixToScale)
    DEREGISTER_NODE(MatrixToShear)

    return status;
}
