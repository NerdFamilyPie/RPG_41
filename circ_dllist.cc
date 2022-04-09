/**
 * Created by Kalpathi Subramanian, 2/20/18
 * krs@uncc.edu
 */

#include "Bridges.h"
#include "CircDLelement.h"
#include "StudentInfo.h"
#include "actor.cc"


using namespace bridges;

// helper function
CircDLelement<Actors> *insertFront(
	CircDLelement<Actors> *tailElement,
	CircDLelement<Actors> *newElement);

int main(int argc, char **argv) {
    Bridges *bridges =  new Bridges(314, "Nerdpie_Cromwell",
                                "795489986107");



	bridges->setTitle("Epic Player's R' US");

	// create the linked list elements with
	// student data
	CircDLelement<Actors> *peeps[] = {
		new CircDLelement<Actors>(
				Actors(
					10,
					5,
					10,
					"Hero",
					"Peggy"
					),""),
		new CircDLelement<Actors>(
				Actors(
					5,
					10,
					5,
					"Villian",
					"Deku"
					),""),
		new CircDLelement<Actors> (
				Actors(
					2,
					2,
					2,
					"Hero",
					"Lennox"
					),"")
	
	};

	CircDLelement<Actors> *head =  nullptr;

	int num_students = 3;
	for (int i = 0; i < num_students; i++) {
		if (i)
			head = insertFront(head, peeps[i]);
		else
			head = peeps[i];
	}

	//  add visual attributes
	CircDLelement<Actors> *current = head;
	Actors si;
	do {
		si = current->getValue();
		current->setLabel(si.GetName());
		current->getVisualizer()->setColor("blue");

		current->getLinkVisualizer(current->getNext())->setColor("green");
		current->getLinkVisualizer(current->getNext())->setThickness(si.GetSpeed());

		current->getLinkVisualizer(current->getPrev())->setColor("red");
		current->getLinkVisualizer(current->getPrev())->setThickness(si.GetHealth());

		current = current->getNext();
	}  while (current != head);

	// set data structure to point to head
	bridges->setDataStructure(head);
	// visualize the circular list
	bridges->visualize();

	return 0;
}

CircDLelement<Actors> *insertFront(
	CircDLelement<Actors> *tailElement,
	CircDLelement<Actors> *newElement) {

	CircDLelement<Actors> *tailNextElement = tailElement->getNext();

	newElement->setNext(tailNextElement);
	newElement->setPrev(tailElement);

	tailNextElement->setPrev(newElement);
	tailElement->setNext(newElement);

	return tailElement;
}
