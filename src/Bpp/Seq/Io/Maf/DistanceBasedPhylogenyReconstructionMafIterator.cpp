//
// File: DistanceBasedPhylogenyReconstructionMafIterator.cpp
// Created by: Julien Dutheil
// Created on: Jul 24 2012
//

/*
Copyright or © or Copr. Bio++ Development Team

This software is a computer program whose purpose is to test the
homogeneity of the substitution process of a given alignment.

This software is governed by the CeCILL  license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#include "DistanceBasedPhylogenyReconstructionMafIterator.h"

#include <Bpp/Seq/DistanceMatrix.h>

using namespace bpp;
using namespace std;

std::unique_ptr<Tree> DistanceBasedPhylogenyReconstructionMafIterator::buildTreeForBlock(const MafBlock& block)
{
  //First get the distance matrix for this block:
  if (!block.hasProperty(distanceProperty_))
    throw Exception("DistanceBasedPhylogenyReconstructionMafIterator::buildTreeForBlock. No property available for " + distanceProperty_);
  try {
    const DistanceMatrix& dist = dynamic_cast<const DistanceMatrix&>(block.getProperty(distanceProperty_));
    builder_->setDistanceMatrix(dist);
    builder_->computeTree();
    auto& tree = builder_->tree();
    return std::unique_ptr<Tree>(tree.clone());
  } catch (bad_cast& e) {
    throw Exception("DistanceBasedPhylogenyReconstructionMafIterator::buildTreeForBlock. A property was found for '" + distanceProperty_ + "' but does not appear to contain a distance matrix.");
  } catch (Exception& e) {
      throw Exception("DistanceBasedPhylogenyReconstructionMafIterator::buildTreeForBlock. Tree reconstruction failed!");
  }
}

