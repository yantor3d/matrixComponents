/**
    Copyright (c) 2018 Ryan Porter
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
extractMatrixScale node
This node returns the scale component of the input matrix as a vector.

    matrix (m) matrix

    output (o) double3
        outputX (ox)
        outputY (oy)
        outputZ (oz)
*/

#include "matrixToScaleNode.h"

#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnData.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnNumericData.h>
#include <maya/MMatrix.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MTypeId.h>


// Input Attributes
MObject MatrixToScale::matrixAttr;


// Output Attributes
MObject MatrixToScale::outputAttr;
    MObject MatrixToScale::outputXAttr;
    MObject MatrixToScale::outputYAttr;
    MObject MatrixToScale::outputZAttr;


void* MatrixToScale::creator()
{
    return new MatrixToScale();
}


MStatus MatrixToScale::initialize()
{
    MStatus status;

    MFnMatrixAttribute m;
    MFnNumericAttribute n;

    matrixAttr = m.create("matrix", "m", MFnMatrixAttribute::Type::kDouble, &status);

    outputXAttr = n.create("outputX", "ox", MFnNumericData::kDouble, 0.0, &status);
    outputYAttr = n.create("outputY", "oy", MFnNumericData::kDouble, 0.0, &status);
    outputZAttr = n.create("outputZ", "oz", MFnNumericData::kDouble, 0.0, &status);

    outputAttr = n.create("output", "o", outputXAttr, outputYAttr, outputZAttr, &status);
    n.setWritable(false);
    n.setStorable(false);

    addAttribute(matrixAttr);
    addAttribute(outputAttr);

    attributeAffects(matrixAttr, outputAttr);

    return MStatus::kSuccess;
}


MStatus MatrixToScale::compute(const MPlug& plug, MDataBlock& data)
{
    MStatus status;

    if (plug == this->outputAttr || plug.parent() == this->outputAttr)
    {
        MMatrix mat = data.inputValue(matrixAttr).asMatrix();
        MTransformationMatrix t(mat);

        t.getScale(scale, MSpace::kWorld);
        
        MDataHandle outX = data.outputValue(outputXAttr);
        MDataHandle outY = data.outputValue(outputYAttr);
        MDataHandle outZ = data.outputValue(outputZAttr);

        outX.setDouble(scale[0]);
        outY.setDouble(scale[1]);
        outZ.setDouble(scale[2]);

        outX.setClean();
        outY.setClean();
        outZ.setClean();

        data.setClean(outputAttr);
    } else {
        return MStatus::kUnknownParameter;
    }

    return MStatus::kSuccess;   
}