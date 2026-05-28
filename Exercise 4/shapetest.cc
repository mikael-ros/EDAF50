/*
 * shapetest.cc: create three objects, check their identity.
 */

#include "shape.h"
#include "square.h"
#include "circle.h"

int main() {
	/*
	 * Create three objects.
	 */
	Shape aShape;
	Square aSquare;
	Circle aCircle;
	
	/*
	 * Call print() in each object to check the kind of object.
	 * The output should be I'm a Shape / Square / Circle
	 */
	aShape.print();
	aSquare.print();
	aCircle.print();
	
	/*
	 * Call print() on the _same_ objects via a Shape* pointer. 
	 * The output should be the same as above, but becomes
	 * Shape / Shape / Shape instead.
	 */
	Shape* psh = &aShape;
	Shape* psq = &aSquare;
	Shape* pci = &aCircle;
	psh->print();
	psq->print();
	pci->print();
}
