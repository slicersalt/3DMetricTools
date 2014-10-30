#include "dataM.h"
#include "vtkCellArray.h"
#include "vtkProperty.h"

int testPolyData(vtkSmartPointer<vtkPolyData> inData , vtkSmartPointer<vtkPolyData> outData );

int main( int argc , char* argv[] )
{
    std::cout << " BEGIN TEST  ----> DATAM.H " << std::endl;

    if( argc < 2 )
    {
      std::cerr << argv[0] << " file1.vtk" << std::endl ;
      return EXIT_FAILURE ;
    }
    dataM dataTest;

    //**************************************************************************************
    std::cout << " Test : Name " << std::endl;
    std::string inName = argv[1] ;
    std::string outName = "out";
    dataTest.setName( inName );
    outName = dataTest.getName();
    if( outName != inName )
    {
        std::cout << " ERROR : name " << std::endl;
        return EXIT_FAILURE;
    }

    //**************************************************************************************
    std::cout << " Test : Opacity " << std::endl;
    double inOpacity = 0.95;
    double outOpacity = 0.0;
    dataTest.setOpacity( inOpacity );
    outOpacity = dataTest.getOpacity();
    if( outOpacity != inOpacity )
    {
        std::cout << " ERROR : opacity " << std::endl;
        return EXIT_FAILURE;
    }

    //**************************************************************************************
    std::cout << " Test : Color " << std::endl;
    double inRed = 0.5;
    double outRed = 0.0;
    double inBlue = 0.3;
    double outBlue = 0.0;
    double inGreen = 0.654;
    double outGreen = 0.0;
    dataTest.setColor( inRed , inGreen , inBlue );
    outRed = dataTest.getRed();
    outGreen = dataTest.getGreen();
    outBlue = dataTest.getBlue();
    if( outRed != inRed || outBlue != inBlue || outGreen != inGreen )
    {
        std::cout << " ERROR : color " << std::endl;
        return EXIT_FAILURE;
    }

    //**************************************************************************************
    std::cout << " Test : Type " << std::endl;
    int inType = 2;
    int outType = 1;
    dataTest.setType( inType );
    outType = dataTest.getType();
    if( outType != inType )
    {
        std::cout << " ERROR : type " << std::endl;
        return EXIT_FAILURE;
    }

    //**************************************************************************************
    std::cout << " Test : getActor | updateproperties " << std::endl;
    vtkSmartPointer <vtkActor> outActor = vtkSmartPointer <vtkActor>::New();
    dataTest.setTypeFile( 1 ) ; // 1 = vtk
    dataTest.initialization();
    outActor = dataTest.getActor();

    outOpacity = outActor -> GetProperty() -> GetOpacity();
    outActor -> GetProperty() -> GetColor( outRed , outGreen , outBlue );
    if( outOpacity != inOpacity || outRed != inRed || outBlue != inBlue || outGreen != inGreen )
    {
        std::cout << " ERROR : actor properties " << std::endl;
        return EXIT_FAILURE;
    }

    //**************************************************************************************
    std::cout << " Test : update type display " << std::endl;
    outType = outActor -> GetProperty() -> GetRepresentation();
    if( outType != 0 )
    {
        std::cout << " ERROR : type display " << std::endl;
        return EXIT_FAILURE;
    }

    //**************************************************************************************
    /*std::cout << " Test : NumberIteration " << std::endl;
    int inNumberIteration = 500;
    int outNumberIteration = 0;
    dataTest.setNumberOfIterationSmooth( inNumberIteration );
    outNumberIteration = dataTest.getNumberOfIterationSmooth();
    if( outNumberIteration != inNumberIteration )
    {
        std::cout << " ERROR : number iteration " << std::endl;
        return EXIT_FAILURE;
    }*/

    //**************************************************************************************
   /* std::cout << " Test : Decimate " << std::endl;
    double inDecimate = 0.14;
    double outDecimate = 0.0;
    dataTest.setDecimate( inDecimate );
    outDecimate = dataTest.getDecimate();
    if( outDecimate != inDecimate )
    {
        std::cout << " ERROR : decimate " << std::endl;
        return EXIT_FAILURE;
    }*/

    //**************************************************************************************
    std::cout << " Test : MisSampFreq " << std::endl;
    double inMinSampFreq = 2.0;
    double outMinSampFreq = 0.0;
    dataTest.setMinSamplingFrequency( inMinSampFreq );
    outMinSampFreq = dataTest.getMinSamplingFrequency();
    if( outMinSampFreq != inMinSampFreq )
    {
        std::cout << " ERROR : min samp freq " << std::endl;
        return EXIT_FAILURE;
    }

    //**************************************************************************************
    std::cout << " Test : SampStep " << std::endl;
    double inSampStep = 0.02;
    double outSampStep = 0.0;
    dataTest.setSamplingStep( inSampStep );
    outSampStep = dataTest.getSamplingStep();
    if( outSampStep != inSampStep )
    {
        std::cout << " ERROR : samp step " << std::endl;
        return EXIT_FAILURE;
    }

    //**************************************************************************************
    std::cout << " Test : SignedDist " << std::endl;
    bool inSignedDist = true;
    bool outSignedDist = false;
    dataTest.setTypeDistance( inSignedDist );
    outSignedDist = dataTest.getTypeDistance();
    if( outSignedDist != inSignedDist )
    {
        std::cout << " ERROR : signed dist " << std::endl;
        return EXIT_FAILURE;
    }

    //**************************************************************************************
    std::cout << " Test : DisplayError " << std::endl;
    bool inDisplayError = true;
    bool outDisplayError = false;
    dataTest.setDisplayError( inDisplayError );
    outDisplayError = dataTest.getDisplayError();
    if( outDisplayError != inDisplayError )
    {
        std::cout << " ERROR : display error " << std::endl;
        return EXIT_FAILURE;
    }

    //**************************************************************************************
    std::cout << " Test : SetPolyData/GetPolyData " << std::endl;

    vtkSmartPointer <vtkPolyData> refData = vtkSmartPointer <vtkPolyData>::New();
    vtkSmartPointer <vtkPolyDataReader> Reader = vtkSmartPointer <vtkPolyDataReader>::New();
    vtkSmartPointer <vtkTriangleFilter> Triangler = vtkSmartPointer <vtkTriangleFilter>::New();
    vtkSmartPointer <vtkCleanPolyData> Cleaner = vtkSmartPointer <vtkCleanPolyData>::New();

    Reader -> SetFileName( argv[1] );
    Reader -> Update();
    Cleaner -> SetInputData( Reader -> GetOutput() );
    Cleaner -> Update();
    Triangler -> SetInputData( Cleaner -> GetOutput() );
    Triangler -> Update();
    refData = Triangler -> GetOutput();
    dataTest.setPolyData( refData );

    vtkSmartPointer <vtkPolyData> outData = vtkSmartPointer <vtkPolyData>::New();

    outData = dataTest.getPolyData();

    if( testPolyData( refData , outData ) == 1 )
    {
        std::cout << " ERROR : getPolyData" << std::endl;
        return EXIT_FAILURE;
    }


    //**************************************************************************************
    std::cout << " Test : getMapper " << std::endl;
    vtkSmartPointer <vtkPolyDataMapper> outMapper = vtkSmartPointer <vtkPolyDataMapper>::New();

    outMapper = dataTest.getMapper();

    if( testPolyData( outMapper -> GetInput() , outData ) == 1 )
    {
        std::cout << " ERROR : getMapper " << std::endl;
        return EXIT_FAILURE;
    }


    //**************************************************************************************
    std::cout << " END TEST " << std::endl;
    return EXIT_SUCCESS;
}

//**********************************************************************************************
int testPolyData( vtkSmartPointer <vtkPolyData> inData , vtkSmartPointer <vtkPolyData> outData )
{
    // comparer pointeurs
    std::cout << "          -number of points  " << outData -> GetNumberOfPoints() << " " <<  inData -> GetNumberOfPoints()<<std::endl;
    if( outData -> GetNumberOfPoints() != inData -> GetNumberOfPoints() )
    {
        std::cout << " ERROR : number of points " << std::endl;
        return 1;
    }

    vtkIdType b = outData -> GetNumberOfCells();
    std::cout << "          -number of cells  " << b << " " << inData -> GetNumberOfCells() << std::endl;
    if( b != inData -> GetNumberOfCells() )
    {
        std::cout << " ERROR : number of cells " << std::endl;
        return 1;
    }


    std::cout << "          -get points  " << std::endl;
    vtkIdType Id = 0;
    double inV[3];
    double outV[3];

    for( Id = 0 ; Id < inData -> GetNumberOfPoints() ; Id++ )
    {
        inData -> GetPoints() -> GetPoint( Id , inV );
        outData -> GetPoints() -> GetPoint( Id , outV );
        if( inV[0] != outV[0] || inV[1] != outV[1] || inV[2] != outV[2] )
        {
            std::cout << " ERROR :  points " << std::endl;
            return 1;
        }

    }

    std::cout << "          -get cells  " << std::endl;
    vtkSmartPointer <vtkIdList> inF = vtkSmartPointer <vtkIdList>::New();
    vtkSmartPointer <vtkIdList> outF = vtkSmartPointer <vtkIdList>::New();
    vtkSmartPointer <vtkCellArray> inPolys = vtkSmartPointer <vtkCellArray> ::New();
    vtkSmartPointer <vtkCellArray> outPolys = vtkSmartPointer <vtkCellArray> ::New();
    inPolys = inData -> GetPolys();
    outPolys = outData -> GetPolys();

    for( Id = 0 ; Id < b ; Id++ )
    {
        inPolys -> GetCell( Id , inF );
        outPolys -> GetCell( Id , outF );

        vtkIdType c = inF->GetNumberOfIds();
        vtkIdType d = outF->GetNumberOfIds();
        if( c!= d && c != 3 )
        {
            return 1 ;
        }
        for( vtkIdType i = 0 ; i < c ; i++ )
        {
            if( inF->GetId(i) != outF->GetId(i) )
            {
                std::cout << " ERROR :  cells " << std::endl;
                return 1;
            }
        }
    }
    return 0;
}
