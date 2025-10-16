Class {
	#name : #Direction,
	#superclass : #Object,
	#instVars : [
		'dx',
		'dy'
	],
	#category : #SnakeGame
}

{ #category : #'instance creation' }
Direction class >> down [
	^ self new initializeDx: 0 dy: 1
]

{ #category : #'instance creation' }
Direction class >> left [
	^ self new initializeDx: -1 dy: 0
]

{ #category : #'instance creation' }
Direction class >> right [
	^ self new initializeDx: 1 dy: 0
]

{ #category : #'instance creation' }
Direction class >> up [
	^ self new initializeDx: 0 dy: -1
]

{ #category : #accessing }
Direction >> dx [
	^ dx
]

{ #category : #accessing }
Direction >> dy [
	^ dy
]

{ #category : #initialization }
Direction >> initializeDx: aDx dy: aDy [
	dx := aDx.
	dy := aDy
]