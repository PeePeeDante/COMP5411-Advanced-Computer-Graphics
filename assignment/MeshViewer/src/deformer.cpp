#include "deformer.h"
#include <iostream>

typedef Eigen::Triplet<double> T;

Deformer::Deformer() : mMesh(nullptr),
                       mCholeskySolver(nullptr) {
}

Deformer::~Deformer() {
	clear();
}

void Deformer::clear() {
	if (mCholeskySolver) {
		delete mCholeskySolver;
	}
	mCholeskySolver = nullptr;
	mRoiList.clear();
}

void Deformer::setMesh(Mesh* mesh) {
	mMesh = mesh;
	clear();
	// Record the handle vertices
	for (Vertex* vert : mMesh->vertices()) {
		if (vert->flag() > 0 || vert->isBoundary()) {
			mRoiList.push_back(vert);
		}
	}
	// Build system matrix for deformation
	buildSystemMat();
}


void Deformer::buildSystemMat() {
	/*====== Programming Assignment 2 ======*/

	/**********************************************/
	/*          Insert your code here.            */
	/**********************************************/
	/*
	/* Build the matrix of the linear system for 
	/* deformation and do factorization, in order
	/* to reuse and speed up in Deformer::deform().
	/* Handle vertices are maked by Vertex::flag() > 0
	/* Movements of the specified handle are already
	/* recorded in Vertex::position()
	/**********************************************/

	Eigen::SparseMatrix< double > systemMat; // transposed matrix
    
	/*====== Programming Assignment 2 ======*/
    
    int V = mMesh->vertices().size();
    int C = mRoiList.size();
    
    mL = new Eigen::SparseMatrix<double>(V+C,V);
    mb = new Eigen::MatrixX3d(V+C,3);
    
    // mL has diagonal all 1
    std::vector< T > tripletList;
    for(int i=0; i< V; i++) {
        tripletList.push_back(T(i,i,1.0));
    }
    
    std::vector<Vertex *>::const_iterator it = mMesh->vertices().begin();
    
    for (; it !=mMesh->vertices().end(); ++it){
        
        OneRingVertex ring(*it);
        std::vector<Vertex *> nb_list;
        
        int nb_size = 0;
        Vertex *curr_nb = nullptr;
        while (curr_nb = ring.nextVertex())
        {
            nb_list.push_back(curr_nb);
            nb_size++;
        }
        
        // record weights and W
        double W = 0;
        std::vector<double> weights;
        Eigen::Vector3f laplace(0, 0, 0);
        
        for (int i = 0; i < nb_size; i++)
        {
            Eigen::Vector3f v1 = (*it)->position() - nb_list[(i + 2) % nb_size]->position();
            Eigen::Vector3f v2 = nb_list[(i + 1) % nb_size]->position() - nb_list[(i + 2) % nb_size]->position();
            double sin_term_1 = (v1.cross(v2)).norm();
            double cos_term_1 = v1.dot(v2);
            double cot1 = cos_term_1 / sin_term_1;

            Eigen::Vector3f v3 = (*it)->position() - nb_list[i % nb_size]->position();
            Eigen::Vector3f v4 = nb_list[(i + 1) % nb_size]->position() - nb_list[i % nb_size]->position();
            double sin_term_2 = (v3.cross(v4)).norm();
            double cos_term_2 = v3.dot(v4);
            double cot2 = cos_term_2 / sin_term_2;

            W += (cot1 + cot2) / 2;
            weights.push_back((cot1 + cot2) / 2);
        }
        
        Eigen::Vector3f delta_i = (*it)->position();
        
        // weights update
        for (int i = 0; i < nb_size; i++){
            tripletList.push_back(T((*it)->index(), nb_list[(i + 1) % nb_size]->index(), -weights[i] / W));
            delta_i -= weights[i] / W * nb_list[(i+1)%nb_size]->position();
        }
        
        // b vector update
        mb->row((*it)->index()) = delta_i.cast<double>();
    }
    
    // constraints update
    for (int i=0; i<C; i++){
        tripletList.push_back(T(V+i, mRoiList[i]->index(), 1.0));
        mb->row(V+i) = mRoiList[i]->position().cast<double>();
    }
    
    mL->setFromTriplets(tripletList.begin(), tripletList.end());
    systemMat = mL->transpose() * (*mL);
    
    // Please refer to the following link for the usage of sparse linear system solvers in Eigen
	// https://eigen.tuxfamily.org/dox/group__TopicSparseSystems.html

	// Do factorization
	if (systemMat.nonZeros() > 0) {
		mCholeskySolver = new Eigen::SimplicialLDLT< Eigen::SparseMatrix< double > >();
		mCholeskySolver->compute(systemMat);
		if (mCholeskySolver->info() != Eigen::Success) {
			// Decomposition failed
			std::cout << "Sparse decomposition failed\n";
		} else {
			std::cout << "Sparse decomposition succeeded\n";
		}
	}
}

void Deformer::deform() {
	if (mCholeskySolver == nullptr) {
		return;
	}

	/*====== Programming Assignment 2 ======*/

	/**********************************************/
	/*          Insert your code here.            */
	/**********************************************/
	/*
	/* This is the place where the editing techniques 
	/* take place.
	/* Solve for the new vertex positions after the 
	/* specified handles move using the factorized
	/* matrix from Deformer::buildSystemMat(), i.e.,
	/* mCholeskySolver defined in deformer.h
	/**********************************************/
    
    int V = mMesh->vertices().size();
    int C = mRoiList.size();
    
    // update constraints in b vector, delta not changed
    for(int i=0; i<C; i++){
        mb->row(V+i) = mRoiList[i]->position().cast<double>();
    }
    
    // solver
    Eigen::MatrixX3d x(V, 3);
    x = mCholeskySolver->solve(mL->transpose() * (*mb));
    
    // update x
    std::vector<Vertex *>::const_iterator it = mMesh->vertices().begin();
    for (; it!=mMesh->vertices().end(); it++) {
        int id = (*it)->index();
        (*it)->setPosition(x.row(id).cast<float>());
    }
    
	// Please refer to the following link for the usage of sparse linear system solvers in Eigen
	// https://eigen.tuxfamily.org/dox/group__TopicSparseSystems.html


	/*====== Programming Assignment 2 ======*/
}
