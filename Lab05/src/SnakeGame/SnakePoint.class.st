Class {
	#name : #SnakePoint,
	#superclass : #Object,
	#instVars : [
		'x',
		'y'
	],
	#category : #SnakeGame
}

{ #category : #initialization }
SnakePoint >> initializeX: aX y: aY [
	x := aX.
	y := aY
]

{ #category : #accessing }
SnakePoint >> x [
	^ x
]

{ #category : #accessing }
SnakePoint >> y [
	^ y
]

{ #category : #comparing }
SnakePoint >> = aPoint [
	^ x = aPoint x and: [ y = aPoint y ]
]

{ #category : #comparing }
SnakePoint >> hash [
	^ x hash bitXor: y hash
]