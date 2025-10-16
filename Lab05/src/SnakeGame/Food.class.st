Class {
	#name : #Food,
	#superclass : #Object,
	#instVars : [
		'position'
	],
	#category : #SnakeGame
}

{ #category : #initialization }
Food >> initializeAtX: aX y: aY [
	position := SnakePoint new initializeX: aX y: aY
]

{ #category : #accessing }
Food >> position [
	^ position
]