#include "dataconfig.h"

DataConfig::DataConfig(QObject *parent) : QObject(parent)
{
    int array0[4][4]={{1,1,1,1},
                    {1,1,0,1},
                    {1,0,0,0},
                    {1,1,0,1}};

    QVector<QVector<int>> v;
    for(int i=0;i<4;i++){
         QVector<int> v1;
         for(int j=0;j<4;j++)
         {
             v1.push_back(array0[i][j]);
         }
         v.push_back(v1);
    }

    mData.insert(0,v);
    v.clear();


    int array1[4][4]={{1,1,1,1},
                    {0,1,1,1},
                    {0,0,1,1},
                    {0,1,1,1}};
    for(int i=0;i<4;i++){
         QVector<int> v1;
         for(int j=0;j<4;j++)
         {
             v1.push_back(array1[i][j]);
         }
         v.push_back(v1);
    }

    mData.insert(1,v);
    v.clear();

    int array2[4][4]={{1,0,1,1},
                    {1,0,0,0},
                    {1,1,0,0},
                    {1,1,1,0}};
    for(int i=0;i<4;i++){
         QVector<int> v1;
         for(int j=0;j<4;j++)
         {
             v1.push_back(array2[i][j]);
         }
         v.push_back(v1);
    }

    mData.insert(2,v);
    v.clear();


    int array19[4][4]={{0,0,0,0},
                    {0,0,0,0},
                    {0,0,0,0},
                    {0,0,0,0}};

    for(int i=0;i<4;i++){
         QVector<int> v1;
         for(int j=0;j<4;j++)
         {
             v1.push_back(array19[i][j]);
         }
         v.push_back(v1);
    }

    mData.insert(19,v);
    v.clear();
}
