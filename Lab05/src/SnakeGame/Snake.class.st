Class {
	#name : #Snake,
	#superclass : #Object,
	#instVars : [
		'body',
		'direction',
		'nextDirection',
		'growing'
	],
	#category : #SnakeGame
}

{ #category : #accessing }
Snake >> body [
	^ body
]

{ #category : #testing }
Snake >> checkSelfCollision [
	| headPos |
	headPos := self head.
	^ body allButFirst anySatisfy: [ :segment | segment = headPos ]
]

{ #category : #actions }
Snake >> grow [
	growing := true
]

{ #category : #accessing }
Snake >> head [
	^ body first
]

{ #category : #initialization }
Snake >> initialize [
	super initialize.
	body := OrderedCollection new.
	self resetToPosition: 10 @ 10
]

{ #category : #accessing }
Snake >> length [
	^ body size
]

{ #category : #actions }
Snake >> move [
	| newHead |
	direction := nextDirection.
	newHead := SnakePoint new
		initializeX: self head x + direction dx
		y: self head y + direction dy.
	
	body addFirst: newHead.
	growing ifFalse: [ body removeLast ].
	growing := false
]

{ #category : #initialization }
Snake >> resetToPosition: aPoint [
	body := OrderedCollection new.
	body add: (SnakePoint new initializeX: aPoint x y: aPoint y).
	body add: (SnakePoint new initializeX: aPoint x - 1 y: aPoint y).
	body add: (SnakePoint new initializeX: aPoint x - 2 y: aPoint y).
	direction := Direction right.
	nextDirection := direction.
	growing := false
]

{ #category : #actions }
Snake >> setDirection: aDirection [
	((aDirection dx + direction dx = 0) and: [ aDirection dy + direction dy = 0 ])
		ifFalse: [ nextDirection := aDirection ]
]