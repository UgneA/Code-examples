package Modified;
import java.util.ArrayList;
/*
     Instances of the class GameState represent states that can arise in the sliding block puzzle.
 */

public class GameState {
    final char[] board;
    static final char[] INITIAL_BOARD = {'L','L','L','L'};
    static final char[] GOAL_BOARD = {'R','R','R','R'};
    static final int BOARD_SIZE = 4;

    /*
        GameState is a constructor that takes a char array holding a board configuration as argument.
     */
    public GameState(char[] board) {
        this.board = board;
    }

    /*
        clone returns a new GameState with the same board configuration as the current GameState.
     */
    public GameState clone() {
        char[] clonedBoard = new char[BOARD_SIZE];
        System.arraycopy(this.board, 0, clonedBoard, 0, BOARD_SIZE);
        return new GameState(clonedBoard);
    }

    /*
        toString returns the board configuration of the current GameState as a printable string.
    */
    public String toString() {
        String s = "[";
        for (char c : this.board) s = s + c;
        return s + "]";
    }

    /*
        isGoal returns true if and only if the board configuration of the current GameState is the goal
        configuration.
    */
    public boolean isGoal() {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (this.board[j] != GOAL_BOARD[j]) return false;
        }
        return true;
    }

    /*
         sameBoard returns true if and only if the GameState supplied as argument has the same board
         configuration as the current GameState.
     */
    public boolean sameBoard (GameState gs) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (this.board[j] != gs.board[j]) return false;
        }
        return true;
    }

    /*
        possibleMoves returns a list of all GameStates that can be reached in a single move from the current GameState.
     */
    public ArrayList<GameState> possibleMoves() {
       ArrayList<GameState> moves = new ArrayList<GameState>();                                                         // creates a list to store possible moves
       for (int start = 0; start < 3; start++) {                                                                        // 0 - represents corn, 1 - goose, 2 - fox, 3 - farmer
           if(board[start]==board[3]) {                                                                                 // if the object that needs to be carried to the other side is on the same side as farmer
               if (board[start] == 'L') {                                                                               // if the object and farmer are on left side of the river
                   GameState newState = this.clone();                                                                   // create a copy of current state
                   newState.board[3] = 'R';                                                                             // farmer crosses river alone

                   if ((newState.board[0] == newState.board[1] && newState.board[3] != newState.board[0]) ||            // if it causes
                           (newState.board[1] == newState.board[2] && newState.board[3] != newState.board[1])) {        // invalid state to occur
                       newState.board[3] = 'L';                                                                         // undo the action
                   } else moves.add(newState);                                                                          // if it does not cause invalid state, add the state to possible moves

                   newState.board[3] = 'R';                                                                             // farmer crosses the river
                   newState.board[start] = 'R';                                                                         // with the object

                   if ((newState.board[0] == newState.board[1] && newState.board[3] != newState.board[0]) ||            // if it causes
                           (newState.board[1] == newState.board[2] && newState.board[3] != newState.board[1])) {        // invalid action to occur
                       newState.board[start] = 'L';                                                                     // undo
                       newState.board[3] = 'L';                                                                         // undo
                   } else  moves.add(newState);                                                                         // otherwise add the state to possible moves
               }
               else {                                                                                                   // if object and farmer are on the right side
                   GameState newState = this.clone();                                                                   // create copy of current state
                   newState.board[3] = 'L';                                                                             // farmer crosses river alone
                   if ((newState.board[0] == newState.board[1] && newState.board[3] != newState.board[0]) ||            // if invalid
                           (newState.board[1] == newState.board[2] && newState.board[3] != newState.board[1])) {        // state occurs
                       newState.board[3] = 'R';                                                                         // undo
                   } else  moves.add(newState);                                                                         // otherwise add the state to possible moves

                   newState.board[3] = 'L';                                                                             // farmer crosses the river
                   newState.board[start] = 'L';                                                                         // with the object

                   if ((newState.board[0] == newState.board[1] && newState.board[3] != newState.board[0]) ||            // if invalid
                           (newState.board[1] == newState.board[2] && newState.board[3] != newState.board[1])) {        // state occurs
                       newState.board[start] = 'R';                                                                     // undo
                       newState.board[3] = 'R';                                                                         // undo
                   } else moves.add(newState);                                                                          // otherwise add the state to possible moves
               }
           }
           else                                                                                                         // if object is not on the same side as the farmer
           {
               GameState newState = this.clone();                                                                       // create copy of current state
               if(newState.board[3]=='L'){                                                                              // if farmer is on the left side
                   newState.board[3]='R';                                                                               // farmer crosses to the right side
                   if ((newState.board[0] == newState.board[1] && newState.board[3] != newState.board[0]) ||            // if invalid
                           (newState.board[1] == newState.board[2] && newState.board[3] != newState.board[1])) {        // state occurs
                       newState.board[3] = 'L';                                                                         // undo
                   } else moves.add(newState);                                                                          // otherwise add the state to possible moves
               }
               else{                                                                                                    // if farmer is on the right side
                   newState.board[3]='L';                                                                               // farmer crosses to the left side
                   if ((newState.board[0] == newState.board[1] && newState.board[3] != newState.board[0]) ||            // if invalid
                           (newState.board[1] == newState.board[2] && newState.board[3] != newState.board[1])) {        // state occurs
                       newState.board[3] = 'R';                                                                         // undo
                   } else moves.add(newState);                                                                          // otherwise add the state to possible moves
               }
           }
        }
        return moves;                                                                                                   // return array list with possible moves
    }
}