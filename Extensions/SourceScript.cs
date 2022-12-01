using Bonsai;
using System;
using System.ComponentModel;
using Bonsai.Vision;
using OpenCV.Net;

[Combinator]
[Description("A camera capture with explicit fps control.")]
[WorkflowElementCategory(ElementCategory.Source)]
public class FpsCameraCapture
{
    readonly CameraCapture capture = new CameraCapture

    {
        CaptureProperties =
        {
            new CapturePropertyAssignment { Property = CaptureProperty.Fps, Value = 0 },
            new CapturePropertyAssignment { Property = CaptureProperty.Settings, Value = 0}
        }
    };

    public int Index
    {
        get { return capture.Index; }
        set { capture.Index = value; }
    }

    public double Fps
    {
        get { return capture.CaptureProperties[0].Value; }
        set { capture.CaptureProperties[0].Value = value; }
    }

    public double Settings
    {
        get { return capture.CaptureProperties[1].Value; }
        set { capture.CaptureProperties[1].Value = value; }
    }

    public IObservable<IplImage> Process()
    {
        return capture.Generate();
        
    }

    

    
}

