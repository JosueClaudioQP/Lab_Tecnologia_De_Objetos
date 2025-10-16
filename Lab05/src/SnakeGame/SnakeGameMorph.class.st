Class {
	#name : #SnakeGameMorph,
	#superclass : #BorderedMorph,
	#instVars : [
		'game',
		'cellSize',
		'stepTime'
	],
	#category : #SnakeGame
}

{ #category : #drawing }
SnakeGameMorph >> drawOn: aCanvas [
	| scoreText levelText foodText hudHeight hudRect foodRect |
	super drawOn: aCanvas.
	
	"Dibujar obstáculos"
	game level obstacles do: [ :obstacle |
		| rect |
		rect := Rectangle
			origin: (obstacle x - 1) * cellSize @ ((obstacle y - 1) * cellSize)
			extent: cellSize @ cellSize.
		rect := rect translateBy: self position.
		aCanvas fillRectangle: rect color: Color gray ].
	
	"Dibujar la serpiente"
	game snake body doWithIndex: [ :segment :index |
		| rect color |
		rect := Rectangle
			origin: (segment x - 1) * cellSize @ ((segment y - 1) * cellSize)
			extent: cellSize @ cellSize.
		rect := rect translateBy: self position.
		color := index = 1
			ifTrue: [ Color yellow ]
			ifFalse: [ Color green ].
		aCanvas fillRectangle: rect color: color ].
	
	"Dibujar la comida"
	foodRect := Rectangle
		origin: (game food position x - 1) * cellSize @ ((game food position y - 1) * cellSize)
		extent: cellSize @ cellSize.
	foodRect := foodRect translateBy: self position.
	aCanvas fillRectangle: foodRect color: Color red.
	
	"Dibujar fondo del HUD"
	hudHeight := 50.
	hudRect := Rectangle
		origin: self position x @ (self position y + (game level height * cellSize) - hudHeight)
		extent: (game level width * cellSize) @ hudHeight.
	aCanvas fillRectangle: hudRect color: (Color black alpha: 0.7).
	
	"Dibujar HUD"
	scoreText := 'Score: ' , game score asString.
	levelText := '  Level: ' , game currentLevel asString.
	foodText := '  Food: ' , game foodEaten asString , '/' , game level foodRequired asString.
	
	aCanvas
		drawString: scoreText , levelText , foodText
		at: self position + (10 @ (game level height * cellSize - 40))
		font: (LogicalFont familyName: 'Arial' pointSize: 14)
		color: Color white.
	
	"Nombre del nivel"
	aCanvas
		drawString: game level name
		at: self position + (10 @ (game level height * cellSize - 20))
		font: (LogicalFont familyName: 'Arial' pointSize: 12)
		color: Color cyan.
	
	"Dibujar Game Over"
	game isGameOver ifTrue: [
		| msg |
		msg := 'GAME OVER - Press R to restart'.
		aCanvas
			drawString: msg
			at: self position + (50 @ (game level height * cellSize // 2))
			font: (LogicalFont familyName: 'Arial' pointSize: 14)
			color: Color yellow ].
	
	"Dibujar Victoria"
	game hasWon ifTrue: [
		| msg |
		msg := 'YOU WIN! All levels completed!'.
		aCanvas
			drawString: msg
			at: self position + (40 @ (game level height * cellSize // 2))
			font: (LogicalFont familyName: 'Arial' pointSize: 14)
			color: Color green ]
]

{ #category : #'event handling' }
SnakeGameMorph >> handlesKeyboard: evt [
	^ true
]

{ #category : #initialization }
SnakeGameMorph >> initialize [
	super initialize.
	game := SnakeGame new.
	cellSize := 20.
	self updateStepTime.
	self extent: game level width * cellSize @ (game level height * cellSize).
	self color: Color black.
	self borderWidth: 2.
	self borderColor: Color white.
	self startStepping
]

{ #category : #'event handling' }
SnakeGameMorph >> keyStroke: evt [
	evt keyCharacter = $w ifTrue: [ game setDirection: Direction up ].
	evt keyCharacter = $s ifTrue: [ game setDirection: Direction down ].
	evt keyCharacter = $a ifTrue: [ game setDirection: Direction left ].
	evt keyCharacter = $d ifTrue: [ game setDirection: Direction right ].
	evt keyCharacter = $r ifTrue: [
		(game isGameOver or: [ game hasWon ]) ifTrue: [
			game := SnakeGame new.
			self updateStepTime.
			self changed ] ]
]

{ #category : #stepping }
SnakeGameMorph >> step [
	(game isGameOver not and: [ game hasWon not ]) ifTrue: [
		game update.
		self updateStepTime.
		self changed ]
]

{ #category : #stepping }
SnakeGameMorph >> stepTime [
	^ stepTime
]

{ #category : #initialization }
SnakeGameMorph >> updateStepTime [
	stepTime := game level speed
]