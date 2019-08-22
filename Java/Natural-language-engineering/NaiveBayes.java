//Ugne Aleknaviciute 1402147

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;



public class NaiveBayes {

    public static ArrayList<String> class_corp0;
    public static ArrayList<String> class_corp1;
    public static ArrayList<String> vocab;
    public static HashMap<String, Double> class0_probs = new HashMap<>();
    public static HashMap<String, Double> class1_probs = new HashMap<>();

    static int class0_C = 0, class1_C = 0;
    static double doc_C = 0;

    //total count of words in documents with class 0 or 1
    static int c0 = 0, c1 = 0;

    /**Counts how many times a class was assigned to a document and
     * how many documents there were in total*/
    public static void classProb(String c[]){
        doc_C++;

        switch (c[1]){
            case"0": {class0_C++;
                break;
            }
            case "1": {class1_C++;
                break;
            }
        }
    }

    /**counts probability of a feature given a certain class
     * returns a smoothed version*/
    public static double feature (String word,int cl, ArrayList<String> corpus, int vocab_size){

        double result = -1;
        double n = 1;

        switch (cl){
            case 0: {
                for(String s: corpus){
                    if(s.equals(word)) n++;
                }
                result = n/(c0+vocab_size);
                break;
            }
            case 1: {
                for(String s: corpus){
                    if(s.equals(word)) n++;
                }
                result = n/(c1+vocab_size);
                break;
            }
        }
        return result;
    }


    /**Perform prediction of a class on training data
     * */
    public static String test(String[] sentence){

        double cl_0 = class0_C/doc_C;
        double cl_1 = class1_C/doc_C;

        for(int i = 2 ; i<sentence.length; i++){
            cl_0 *= class0_probs.get(sentence[i]);
            cl_1 *= class1_probs.get(sentence[i]);
        }

        return cl_0 > cl_1? "0" : "1";
    }


    public static void main(String[] args) {
        try {
            class_corp0 = new ArrayList<>();    //words that occur in documents that belong to class0
            class_corp1 = new ArrayList<>();    //words that occur in documents that belong to class1
            vocab = new ArrayList<>();
            int v_size;

            String line;
            //double count=0;

            //reads in vocabulary file and store values in an ArrayList
            String dir = System.getProperty("user.dir");
            File v = new File(dir+"\\sampleTrain.vocab.txt");

            Scanner in = new Scanner(v);
            while (in.hasNext()){
                vocab.add(in.next());
            }
            v_size = vocab.size();

            /**Reads in training data file
             * performs calculations of variables to be used in class prediction
             * Adds words that belong to document of class 0/1 to corresponding ArrayLists
             * */
            BufferedReader br = new BufferedReader(new FileReader(dir+"\\sampleTrain.txt"));
            while( (line = br.readLine()) != null){

                String  temp[] =(line.split("\\s+"));
                classProb(temp);

                for(int i = 2 ; i<temp.length; i++){
                    if(temp[1].equals("0")) {
                        class_corp0.add(temp[i]);
                        c0++;
                    }
                    else{
                        class_corp1.add(temp[i]);
                        c1++;
                    }
                    //count++;
                }
            }


            // prints prior class probabilities
            System.out.println("Prior probabilities");
            System.out.println("class 0 = "+class0_C/doc_C);
            System.out.println("class 1 = "+class1_C/doc_C+"\n");

            //calculates and prints features likelihoods for a certain (0 or 1) class
            System.out.println("Feature likelihoods");
            System.out.print("          ");
            for(String s : vocab){
                System.out.printf("%-12s",s);
            }
            System.out.println();

            System.out.print("class 0 = ");
            for(String s: vocab){
                double prob = feature(s,0,class_corp0,v_size);
                class0_probs.put(s,prob);
                System.out.printf("%-9.2f %2s",prob,"");
            }
            System.out.print("\nclass 1 = ");
            for(String s: vocab){
                double prob = feature(s,1,class_corp1,v_size);
                class1_probs.put(s,prob);
                System.out.printf("%-9.2f %2s",prob,"");
            }

            /**Reads in test data and prints out predicted class for a document and prediction accuracy
             * correct/n is a measure of how many classes were predicted correctly
             * int correct - number of correctly documents with correctly predicted classes
             * int n - number of documents
             * */
            System.out.println("\n\nPredictions on test data");
            BufferedReader br1 = new BufferedReader(new FileReader(dir+"\\sampleTest.txt"));

            int n = 0;
            double correct = 0;
            while( (line = br1.readLine()) != null){
                String  temp[] =(line.split("\\s+"));
                System.out.print(temp[0]+" = Class ");
                String prediction = test(temp);
                System.out.println(prediction);

                n++;
                if( prediction.equals(temp[1]) ){
                    correct++ ;
                }
            }
            System.out.printf("\nAccuracy on test data = "+"%.4f %n",correct/n);

        }catch(Exception e){e.printStackTrace();}
    }
}