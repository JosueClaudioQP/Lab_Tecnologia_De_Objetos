Class {
	#name : #SnakeGame,
	#superclass : #Object,
	#instVars : [
		'snake',
		'food',
		'score',
		'gameOver',
		'currentLevel',
		'level',
		'foodEaten',
		'won'
	],
	#category : #SnakeGame
}

{ #category : #accessing }
SnakeGame >> currentLevel [
	^ currentLevel
]

{ #category : #accessing }
SnakeGame >> food [
	^ food
]

{ #category : #accessing }
SnakeGame >> foodEaten [
	^ foodEaten
]

{ #category : #testing }
SnakeGame >> hasWon [
	^ won
]

{ #category : #initialization }
SnakeGame >> initialize [
	super initialize.
	currentLevel := 1.
	score := 0.
	gameOver := false.
	won := false.
	foodEaten := 0.
	self loadLevel: currentLevel
]

{ #category : #testing }
SnakeGame >> isGameOver [
	^ gameOver
]

{ #category : #accessing }
SnakeGame >> level [
	^ level
]

{ #category : #actions }
SnakeGame >> loadLevel: levelNumber [
	level := Level new initializeLevel: levelNumber.
	snake := Snake new.
	snake resetToPosition: level getStartPosition.
	foodEaten := 0.
	self spawnFood
]

{ #category : #accessing }
SnakeGame >> score [
	^ score
]

{ #category : #actions }
SnakeGame >> setDirection: aDirection [
	snake setDirection: aDirection
]

{ #category : #accessing }
SnakeGame >> snake [
	^ snake
]

{ #category : #actions }
SnakeGame >> spawnFood [
	| validPosition |
	validPosition := false.
	[ validPosition ] whileFalse: [
		| x y pos |
		x := (1 to: level width) atRandom.
		y := (1 to: level height) atRandom.
		pos := SnakePoint new initializeX: x y: y.
		validPosition := (snake body noneSatisfy: [ :segment | segment = pos ])
			and: [ (level hasObstacleAt: pos) not ].
		validPosition ifTrue: [ food := Food new initializeAtX: x y: y ] ]
]

{ #category : #updating }
SnakeGame >> update [
	gameOver ifTrue: [ ^ self ].
	won ifTrue: [ ^ self ].
	
	snake move.
	
	"Verificar colisión con paredes"
	(snake head x < 1 or: [ snake head x > level width ]) ifTrue: [ 
		gameOver := true. 
		^ self ].
	(snake head y < 1 or: [ snake head y > level height ]) ifTrue: [ 
		gameOver := true. 
		^ self ].
	
	"Verificar colisión con obstáculos"
	(level hasObstacleAt: snake head) ifTrue: [
		gameOver := true.
		^ self ].
	
	"Verificar colisión consigo misma"
	snake checkSelfCollision ifTrue: [ gameOver := true. ^ self ].
	
	"Verificar colisión con comida"
	(snake head = food position) ifTrue: [
		snake grow.
		score := score + 10.
		foodEaten := foodEaten + 1.
		
		"Verificar si pasa de nivel"
		foodEaten >= level foodRequired ifTrue: [
			currentLevel := currentLevel + 1.
			currentLevel > 5
				ifTrue: [ won := true ]
				ifFalse: [ self loadLevel: currentLevel ] ]
		ifFalse: [ self spawnFood ] ]
]