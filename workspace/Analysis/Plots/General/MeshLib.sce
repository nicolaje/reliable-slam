// Library adapted from : http://www.morere.eu/spip.php?article142
// Requires the use of the lib3ds library
// The sub mesh is here: /home/jem/reliable-slam/workspace/Analysis/Plots/General/submarine.sce
function [X,Y,Z]=loadSCEMesh(fileName)
    exec(fileName);
    facelist1 = facelist1 + 1;
    X = matrix(vertices1(facelist1,1),size(facelist1,1),length(vertices1(facelist1,1))/size(facelist1,1))';
    Y = matrix(vertices1(facelist1,2),size(facelist1,1),length(vertices1(facelist1,1))/size(facelist1,1))';
    Z = matrix(vertices1(facelist1,3),size(facelist1,1),length(vertices1(facelist1,1))/size(facelist1,1))'; 
endfunction

function meshHandle=plotMesh(fileName)
    [X,Y,Z]=loadSCEMesh(fileName);
    meshHandle=plot3d(X,Y,Z);
endfunction

function [X,Y,Z]=transformMesh(X,Y,Z,rotation,translation)
    
endfunction

function updateMesh(meshHandle,X,Y,Z)
    
endfunction