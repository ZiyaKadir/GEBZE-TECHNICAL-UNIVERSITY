import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.lang.System;



//general annonucment
// notify moethod directly connected with observers in this way observers will notify when the data is changing 
//this is a observer pattern
// notify mothod is running for adding and removing part

interface Playable {
    void info();
    String get_name();
}

interface NonPlayable {
    void info();
    String get_name();
}

interface Visual {
    void display();
}

interface NonVisual {
    void display();
}

interface Observable{
    void register(Observer observer);
    void unregister(Observer observer);
    void notifyObservers();
}

interface Observer {
    void update(Dataset data);
}


// Dataset it is like my main server which notify the observers which are registered
class Dataset implements Observable {
    private List<Data> dataList;
    private List<Observer> observers;

    public Dataset() {
        dataList = new ArrayList<>();
        observers = new ArrayList<>();
    }

    @Override
    public void register(Observer observer) {
        observers.add(observer);
    }

    @Override
    public void unregister(Observer observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers() {
        for (Observer observer : observers) {
            observer.update(this);
        }
    }

    public void add(Data data) {
        dataList.add(data);
        notifyObservers();
    }

    public void remove(Data data) {
        dataList.remove(data);
        notifyObservers();
    }

    public List<Data> getDataList() {
        return dataList;
    }
}
//Data is the hold information about everythink this s base class
class Data {
    private String name;
    private String info;

    Data(String name, String info) {
        this.name = name;
        this.info = info;
    }

    public String get_name() {
        return name;
    }

    public String get_info() {
        return info;
    }
}

//derived class Image
class Image extends Data implements NonPlayable, Visual {
    private String dimension;

    public Image(String name, String dimension, String info) {
        super(name, info);
        this.dimension = dimension;
    }

    public String get_dimension() {
        return dimension;
    }

    @Override
    public void info() {
        System.out.println("Image Info: " + get_info());
    }

    @Override
    public String get_name() {
        return super.get_name();
    }

    @Override
    public void display() {
        System.out.println("Displaying Image: " + get_name());
    }
}
//derived class for audio
class Audio extends Data implements NonVisual, Playable {
    private String duration;

    public Audio(String name, String duration, String info) {
        super(name, info);
        this.duration = duration;
    }

    public String get_duration() {
        return duration;
    }

    @Override
    public void info() {
        System.out.println("Audio Info: " + get_info());
    }

    @Override
    public String get_name() {
        return super.get_name();
    }

    @Override
    public void display() {
        System.out.println("Cannot display audio.");
    }


}
//derived class for video
class Video extends Data implements Playable, Visual {
    private String duration;

    public Video(String name, String duration, String info) {
        super(name, info);
        this.duration = duration;
    }

    public String get_duration() {
        return duration;
    }

    @Override
    public void info() {
        System.out.println("Video Info: " + get_info());
    }

    @Override
    public String get_name() {
        return super.get_name();
    }

    @Override
    public void display() {
        System.out.println("Displaying Video: " + get_name());
    }
}
//derived class for Text
class Text extends Data implements NonPlayable, NonVisual {
    public Text(String name, String info) {
        super(name, info);
    }

    @Override
    public void info() {
        System.out.println("Text Info: " + get_info());
    }

    @Override
    public String get_name() {
        return super.get_name();
    }

    @Override
    public void display() {
        System.out.println("Cannot display text.");
    }
}


// Player for my Playlable object 
class Player implements Observer {
    private List<Playable> playlist;
    private int currentIdx;

    public Player() {
        playlist = new ArrayList<>();
        currentIdx = 0;
    }

    public void add(Playable playable) {
        playlist.add(playable);
    }

    public void remove(Playable playable) {
        playlist.remove(playable);
    }

    public void showPlaylist() {
        System.out.println("Playlist:");
        for (Playable playable : playlist) {
            System.out.println(playable.get_name());
        }
    }

    public void currentlyPlaying() {
        if (playlist.isEmpty()) {
            System.out.println("No item is currently playing.");
        } else {
            Playable currentlyPlaying = playlist.get(currentIdx);
            currentlyPlaying.info();
        }
    }

    public void next(String type) {

        if (playlist.isEmpty()) {
            System.out.println("No item in the playlist.");
            return;
        }
        //control what is the type
        if (type.equals("audio")) {
            for (int i = currentIdx + 1; i < playlist.size(); i++) {
                if (playlist.get(i) instanceof Audio) {
                    currentIdx = i;
                    return;
                }
            }
        } else if (type.equals("video")) {
            for (int i = currentIdx + 1; i < playlist.size(); i++) {
                if (playlist.get(i) instanceof Video) {
                    currentIdx = i;
                    return;
                }
            }
        }

        System.out.println("No " + type + " item found in the playlist.");
    }

    public void previous(String type) {
        if (playlist.isEmpty()) {
            System.out.println("No item in the playlist.");
            return;
        }
        //control what is the type
        if (type.equals("audio")) {
            for (int i = currentIdx - 1; i >= 0; i--) {
                if (playlist.get(i) instanceof Audio) {
                    currentIdx = i;
                    return;
                }
            }
        } else if (type.equals("video")) {
            for (int i = currentIdx - 1; i >= 0; i--) {
                if (playlist.get(i) instanceof Video) {
                    currentIdx = i;
                    return;
                }
            }
        }

        System.out.println("No " + type + " item found in the playlist.");
    }

    @Override
    public void update(Dataset data) {
        List<Data> dataList = data.getDataList();
    
        // Clear the view list
        playlist.clear();
        currentIdx = 0;
    
        // Add playable objects to the view list
        for (Data dataItem : dataList) {
            if (dataItem instanceof Playable) {
                add((Playable) dataItem);
            }
        }
    }
    
}

// Viewer for my nonplaylable object
class Viewer implements Observer {
    private List<NonPlayable> viewList;
    private int currentIdx;
    Dataset data; // Dataset object helps for notify according to Dataset

    public Viewer() {
        viewList = new ArrayList<>();
        currentIdx = 0;
    }

    public void add(NonPlayable nonPlayable) {
        viewList.add(nonPlayable);
    }

    public void remove(NonPlayable nonPlayable) {
        viewList.remove(nonPlayable);
    }

    public void show() {
        System.out.println("View List:");
        for (NonPlayable nonPlayable : viewList) {
            System.out.println(nonPlayable.get_name());
        }
    }

    public void currentlyViewing() {
        if (viewList.isEmpty()) {
            System.out.println("No item is currently being viewed.");
        } else {
            NonPlayable currentlyViewing = viewList.get(currentIdx);
            currentlyViewing.info();
        }
    }

    public void next(String type) {
        if (viewList.isEmpty()) {
            System.out.println("No item in the view list.");
            return;
        }

        //control what is the type
        if (type.equals("text")) {
            for (int i = currentIdx + 1; i < viewList.size(); i++) {
                if (viewList.get(i) instanceof Text) {
                    currentIdx = i;
                    return;
                }
            }
        } else if (type.equals("image")) {
            for (int i = currentIdx + 1; i < viewList.size(); i++) {
                if (viewList.get(i) instanceof Image) {
                    currentIdx = i;
                    return;
                }
            }
        }

        System.out.println("No " + type + " item found in the view list.");
    }

    public void previous(String type) {
        if (viewList.isEmpty()) {
            System.out.println("No item in the view list.");
            return;
        }
        //control what is the type
        if (type.equals("text")) {
            for (int i = currentIdx - 1; i >= 0; i--) {
                if (viewList.get(i) instanceof Text) {
                    currentIdx = i;
                    return;
                }
            }
        } else if (type.equals("image")) {
            for (int i = currentIdx - 1; i >= 0; i--) {
                if (viewList.get(i) instanceof Image) {
                    currentIdx = i;
                    return;
                }
            }
        }

        System.out.println("No " + type + " item found in the view list.");
    }

    @Override
    public void update(Dataset data) {
        List<Data> dataList = data.getDataList();
    
        // Clear the view list
        viewList.clear();
        currentIdx = 0;
    
        // Add playable objects to the view list
        for (Data dataItem : dataList) {
            if (dataItem instanceof NonPlayable) {
                add((NonPlayable) dataItem);
            }
        }
    }
    
}

public class Main {
    public static void main(String[] args) {

        //creating for my object for testing
        Player player = new Player();
        Viewer viewer = new Viewer();
        Dataset dataset = new Dataset();
        dataset.register(player);
        dataset.register(viewer);

        Scanner scanner = new Scanner(System.in);

        //Adding and controlling mechanism for my program
        while (true) {
            System.out.print("Enter command (add, remove, show, next, previous, quit): ");
            String command = scanner.nextLine();

            if (command.equals("add")) {
                System.out.print("Enter data type (audio, video, image, text): ");
                String dataType = scanner.nextLine();

                System.out.print("Enter data name: ");
                String dataName = scanner.nextLine();

                System.out.print("Enter data info: ");
                String dataInfo = scanner.nextLine();

                if (dataType.equals("audio")) {
                    System.out.print("Enter audio duration: ");
                    String audioDuration = scanner.nextLine();
                    Audio audio = new Audio(dataName, audioDuration, dataInfo);
                    dataset.add(audio);
                } else if (dataType.equals("video")) {
                    System.out.print("Enter video duration: ");
                    String videoDuration = scanner.nextLine();
                    Video video = new Video(dataName, videoDuration, dataInfo);
                    dataset.add(video);
                } else if (dataType.equals("image")) {
                    System.out.print("Enter image dimension: ");
                    String imageDimension = scanner.nextLine();
                    Image image = new Image(dataName, imageDimension, dataInfo);
                    dataset.add(image);
                } else if (dataType.equals("text")) {
                    Text text = new Text(dataName, dataInfo);
                    dataset.add(text);
                }
            } else if (command.equals("remove")) {
                System.out.print("Enter data name: ");
                String dataName = scanner.nextLine();
                List<Data> dataList = dataset.getDataList();
                for (Data data : dataList) {
                    if (data.get_name().equals(dataName)) {
                        dataset.remove(data);
                        break;
                    }
                }
            } else if (command.equals("show")) {
                System.out.print("Enter list type (playlist, view list): ");
                String listType = scanner.nextLine();
                if (listType.equals("playlist")) {
                    player.showPlaylist();
                } else if (listType.equals("view list")) {
                    viewer.show();
                }
            } else if (command.equals("next")) {
                System.out.print("Enter list type (audio, video, text, image): ");
                String listType = scanner.nextLine();
                player.next(listType);
                viewer.next(listType);
            } else if (command.equals("previous")) {
                System.out.print("Enter list type (audio, video, text, image): ");
                String listType = scanner.nextLine();
                player.previous(listType);
                viewer.previous(listType);
            } else if (command.equals("quit")) {
                break;
            }
        }
        //collect the garbage value if the System have garbage value Java must doing this but we take a measure
        scanner.close();

        System.gc();
    }
}
