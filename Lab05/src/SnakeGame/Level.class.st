Class {
	#name : #Level,
	#superclass : #Object,
	#instVars : [
		'levelNumber',
		'width',
		'height',
		'obstacles',
		'foodRequired',
		'speed',
		'name'
	],
	#category : #SnakeGame
}

{ #category : #building }
Level >> buildLevel [
	levelNumber = 1 ifTrue: [ self buildLevel1 ].
	levelNumber = 2 ifTrue: [ self buildLevel2 ].
	levelNumber = 3 ifTrue: [ self buildLevel3 ].
	levelNumber = 4 ifTrue: [ self buildLevel4 ].
	levelNumber = 5 ifTrue: [ self buildLevel5 ]
]

{ #category : #building }
Level >> buildLevel1 [
	name := 'Level 1 - Empty Field'.
	foodRequired := 5.
	speed := 150.
	"Sin obstáculos"
]

{ #category : #building }
Level >> buildLevel2 [
	name := 'Level 2 - The Cross'.
	foodRequired := 8.
	speed := 130.
	"Cruz en el centro - con huecos"
	10 to: 13 do: [ :x |
		obstacles add: (SnakePoint new initializeX: x y: 10) ].
	17 to: 20 do: [ :x |
		obstacles add: (SnakePoint new initializeX: x y: 10) ].
	6 to: 8 do: [ :y |
		obstacles add: (SnakePoint new initializeX: 15 y: y) ].
	12 to: 14 do: [ :y |
		obstacles add: (SnakePoint new initializeX: 15 y: y) ]
]

{ #category : #building }
Level >> buildLevel3 [
	name := 'Level 3 - The Boxes'.
	foodRequired := 10.
	speed := 110.
	"Cajas en las esquinas"
	5 to: 8 do: [ :x |
		5 to: 8 do: [ :y |
			obstacles add: (SnakePoint new initializeX: x y: y) ] ].
	22 to: 25 do: [ :x |
		5 to: 8 do: [ :y |
			obstacles add: (SnakePoint new initializeX: x y: y) ] ].
	5 to: 8 do: [ :x |
		13 to: 16 do: [ :y |
			obstacles add: (SnakePoint new initializeX: x y: y) ] ].
	22 to: 25 do: [ :x |
		13 to: 16 do: [ :y |
			obstacles add: (SnakePoint new initializeX: x y: y) ] ]
]

{ #category : #building }
Level >> buildLevel4 [
	name := 'Level 4 - The Maze'.
	foodRequired := 12.
	speed := 90.
	"Laberinto con aberturas"
	8 to: 12 do: [ :x |
		obstacles add: (SnakePoint new initializeX: x y: 6) ].
	18 to: 22 do: [ :x |
		obstacles add: (SnakePoint new initializeX: x y: 6) ].
	8 to: 12 do: [ :x |
		obstacles add: (SnakePoint new initializeX: x y: 14) ].
	18 to: 22 do: [ :x |
		obstacles add: (SnakePoint new initializeX: x y: 14) ].
	6 to: 10 do: [ :y |
		obstacles add: (SnakePoint new initializeX: 8 y: y) ].
	10 to: 14 do: [ :y |
		obstacles add: (SnakePoint new initializeX: 22 y: y) ]
]

{ #category : #building }
Level >> buildLevel5 [
	name := 'Level 5 - The Spiral'.
	foodRequired := 15.
	speed := 70.
	"Espiral con aberturas"
	5 to: 25 do: [ :x |
		obstacles add: (SnakePoint new initializeX: x y: 5) ].
	5 to: 10 do: [ :x |
		obstacles add: (SnakePoint new initializeX: x y: 15) ].
	20 to: 25 do: [ :x |
		obstacles add: (SnakePoint new initializeX: x y: 15) ].
	5 to: 15 do: [ :y |
		obstacles add: (SnakePoint new initializeX: 5 y: y) ].
	5 to: 10 do: [ :y |
		obstacles add: (SnakePoint new initializeX: 25 y: y) ].
	12 to: 15 do: [ :y |
		obstacles add: (SnakePoint new initializeX: 25 y: y) ].
	10 to: 20 do: [ :x |
		obstacles add: (SnakePoint new initializeX: x y: 8) ].
	10 to: 15 do: [ :x |
		obstacles add: (SnakePoint new initializeX: x y: 12) ].
	8 to: 12 do: [ :y |
		obstacles add: (SnakePoint new initializeX: 10 y: y) ].
	8 to: 10 do: [ :y |
		obstacles add: (SnakePoint new initializeX: 20 y: y) ]
]

{ #category : #accessing }
Level >> foodRequired [
	^ foodRequired
]

{ #category : #accessing }
Level >> getStartPosition [
	levelNumber = 1 ifTrue: [ ^ 10 @ 10 ].
	levelNumber = 2 ifTrue: [ ^ 5 @ 5 ].
	levelNumber = 3 ifTrue: [ ^ 15 @ 10 ].
	levelNumber = 4 ifTrue: [ ^ 15 @ 10 ].
	levelNumber = 5 ifTrue: [ ^ 15 @ 10 ].
	^ 10 @ 10
]

{ #category : #testing }
Level >> hasObstacleAt: aPoint [
	^ obstacles anySatisfy: [ :obstacle | obstacle = aPoint ]
]

{ #category : #accessing }
Level >> height [
	^ height
]

{ #category : #initialization }
Level >> initializeLevel: aNumber [
	levelNumber := aNumber.
	width := 30.
	height := 20.
	obstacles := Set new.
	self buildLevel
]

{ #category : #accessing }
Level >> name [
	^ name
]

{ #category : #accessing }
Level >> obstacles [
	^ obstacles
]

{ #category : #accessing }
Level >> speed [
	^ speed
]

{ #category : #accessing }
Level >> width [
	^ width
]