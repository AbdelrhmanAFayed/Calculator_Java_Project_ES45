package com.mycompany.java_module;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.Map;
import java.util.Queue;

/**
 *
 * @author Mousa Mahmoud
 */
public class Calculator {
    private static final Map<Character, Integer> OPERATOR_PRECEDENCIES = new HashMap<>();
    
    static {
        OPERATOR_PRECEDENCIES.put('+', 1);
        OPERATOR_PRECEDENCIES.put('-', 1);
        OPERATOR_PRECEDENCIES.put('*', 2);
        OPERATOR_PRECEDENCIES.put('/', 2);
    }
    
    /**
     * 
     * @param expression the mathematical expression with no spaces
     * @return Result as Double and NaN for invalid expression or undefined result
     */
    public Double getResult(String expression) {
        if (expression == null || expression.length() == 0)
            return Double.NaN;
        
        String[] tokens = tokenize(expression);
        if ((tokens.length % 2 == 0) || 
                ((tokens.length < 2) && (isOperator(tokens[1]))))
            return Double.NaN;
        else if (getNumOfOperators(tokens) > tokens.length / 2)
            return Double.NaN;
        
        Queue<String> outputQueue = new ArrayDeque<>();
        infixToPostfix(tokens, outputQueue);
        
        return evaluateExpression(outputQueue);
    }

    private String[] tokenize(String expression) {
        return expression.split("(?<=[\\+\\-\\*\\/])|(?=[\\+\\-\\*\\/])");
    }

    private void infixToPostfix(String[] tokens, Queue<String> outputQueue) {
        Deque<Character> operatorsStack = new ArrayDeque<>();
        
        for (String token : tokens) {
            if (isOperator(token)) {
                while (!operatorsStack.isEmpty() && 
                        hasHiegherOrEqualPrecedency(operatorsStack.peek(), token.charAt(0))) {
                    outputQueue.offer(operatorsStack.pop().toString());
                }
                operatorsStack.push(token.charAt(0));
            } else {
                outputQueue.offer(token);
            }
        }
        while (!operatorsStack.isEmpty())
            outputQueue.offer(operatorsStack.pop().toString());
    }

    private boolean isOperator(String token) {
        return (token.length() == 1 && 
                (token.charAt(0) == '+') ||
                (token.charAt(0) == '-') ||
                (token.charAt(0) == '*') ||
                (token.charAt(0) == '/')
                );
    }

    private boolean hasHiegherOrEqualPrecedency(char stackTop, char currentOperator) {
        return (OPERATOR_PRECEDENCIES.get(stackTop) >= OPERATOR_PRECEDENCIES.get(currentOperator));
    }

    private Double evaluateExpression(Queue<String> outputQueue) {
        Deque<Double> resultStack = new ArrayDeque<>();
        
        while (!outputQueue.isEmpty()) {
            String firstItem = outputQueue.poll();
            
            if (isOperator(firstItem)) {
                Double operand2 = resultStack.pop(), operand1 = resultStack.pop();
                switch (firstItem.charAt(0)) {
                    case '+': resultStack.push(operand1 + operand2); break;
                    case '-': resultStack.push(operand1 - operand2); break;
                    case '*': resultStack.push(operand1 * operand2); break;
                    case '/': resultStack.push(operand1 / operand2); break;
                    default: throw new AssertionError();
                }
            } else {
                resultStack.push(Double.valueOf(firstItem));
            }
        }
        
        return resultStack.pop();
    }

    private int getNumOfOperators(String[] tokens) {
        int count = 0;
        
        for (String token : tokens)
            if (isOperator(token))
                count++;
        
        return count;
    }
}
