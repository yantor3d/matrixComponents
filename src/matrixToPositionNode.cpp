/**
    Copyright (c) 2018 Ryan Porter
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
extractMatrixPosition node
This node returns the position component of the input matrix as a vector.

    matrix (m) matrix

    output (o) double3
        outputX (ox) double
        outputY (oy) double
        outputZ (oz) double
*/

#include "matrixToPositionNode.h"

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
#include <maya/MTypeId.h>


// Input Attributes
MObject MatrixToPosition::matrixAttr;


// Output Attributes
MObject MatrixToPosition::outputAttr;
    MObject MatrixToPosition::outputXAttr;
    MObject MatrixToPosition::outputYAttr;
    MObject MatrixToPosition::outputZAttr;


void* MatrixToPosition::creator()
{
    return new MatrixToPosition();
}


MStatus MatrixToPosition::initialize()
{
    MStatus status;

    MFnMatrixAttribute  m;
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


MStatus MatrixToPosition::compute(const MPlug& plug, MDataBlock& data)
{
    MStatus status;

    if (plug == this->outputAttr || plug.parent() == this->outputAttr)
    {
        MMatrix mat = data.inputValue(matrixAttr).asMatrix();

        double x = mat(3, 0);
        double y = mat(3, 1);
        double z = mat(3, 2);

        MDataHandle outX = data.outputValue(outputXAttr);
        MDataHandle outY = data.outputValue(outputYAttr);
        MDataHandle outZ = data.outputValue(outputZAttr);

        outX.setDouble(x);
        outY.setDouble(y);
        outZ.setDouble(z);

        outX.setClean();
        outY.setClean();
        outZ.setClean();

        data.setClean(outputAttr);
    } else {
        return MStatus::kUnknownParameter;
    }

    return MStatus::kSuccess;   
}